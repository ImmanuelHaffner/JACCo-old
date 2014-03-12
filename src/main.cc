#include <string>
#include <stdexcept>
#include <iostream>
#include <sstream>

#include "llvm/Support/Signals.h"           /* Nice stacktrace output */
#include "llvm/Support/SystemUtils.h"
#include "llvm/Support/PrettyStackTrace.h"
#include "llvm/Support/raw_ostream.h"       /* Print LLVM IR output */
#include "llvm/IR/Module.h"                 /* Module */
#include "diagnostic.h"
#include "util.h"
#include "Lex/Lexer.h"
#include "Parse/Parser.h"
#include "AST/Printable.h"
#include "Sema/TypeFactory.h"
#include "CodeGen/CodeGen.h"
#include "Optimization/Optimization.h"


using namespace C4;
using namespace Lex;
using namespace Parse;
using namespace AST;
using namespace Sema;
using namespace CodeGen;
using namespace llvm;
using namespace Optimize;


enum class Mode {
  TOKENIZE,
  PARSE,
  PRINT_AST,
  COMPILE,
  OPTIMIZE
};

int main(int argc, char** const argv)
{
  char** i = argv + 1;

  bool symbols = false;

  Mode mode = Mode::COMPILE;
  for (; auto const arg = *i; ++i) {
    if (arg[0] != '-') {
      break;
    } else if (strEq(arg, "--tokenize")) {
      mode = Mode::TOKENIZE;
    } else if (strEq(arg, "--parse")) {
      mode = Mode::PARSE;
    } else if (strEq(arg, "--print-ast")) {
      mode = Mode::PRINT_AST;
    } else if (strEq(arg, "--compile")) {
      mode = Mode::COMPILE;
    } else if (strEq(arg, "--optimize")) {
      mode = Mode::OPTIMIZE;
    } else if (strEq(arg, "--symbols")) {
      symbols = true;
    } else if (strEq(arg, "-")) {
      break;
    } else if (strEq(arg, "--")) {
      ++i;
      break;
    } else {
      errorf("unknown argument '%s'", arg);
    }
  }

  if (!*i)
    errorf("no input files specified");


  if (!hasNewErrors()) {
    Token::INIT_KEYWORDS_TABLE(); // initialize the symbol table for keywords
    for (; char const *name = *i; ++i)
    {
      FILE* f;
      if (strEq(name, "-")) {
        f    = stdin;
        name = "<stdin>";
      } else {
        f = fopen(name, "rb");
        if (!f)
        {
          errorErrno(Pos(name));
          continue;
        }
        fclose( f );
      }

      if (hasNewErrors())
        continue;

      Lexer * const lexer = f == stdin ? new Lexer : new Lexer( name );

      if ( Mode::TOKENIZE == mode )
      {
        while ( true )
        {
          Token const tok = lexer->getToken();
          if ( TK::END_OF_FILE == tok.kind )
            break;
          std::cout << tok.pos << " " << tok << "\n";
        }
        continue;
      }

      Parser parser( *lexer );
      TranslationUnit const * const unit = parser.parse();

      if ( Mode::PARSE == mode ) continue;

      if ( Mode::PRINT_AST == mode )
      {
        unit->print( Printer( std::cout ) );
        continue;
      }

      if ( hasNewErrors() ) continue;

      /* Compile. */
      llvm::sys::PrintStackTraceOnErrorSignal();
      llvm::PrettyStackTraceProgram X(argc, argv);
      CodeGenFunction CGF( name );

      unit->emit( CGF );
      verifyModule( CGF.M );

      Optimizer::runMem2Reg( CGF.M );

      /* Optimize. */
      if ( Mode::OPTIMIZE == mode )
      {
        Optimizer::runSCCP( CGF.M );
        Optimizer::runMem2Reg( CGF.M );

        verifyModule( CGF.M );
      }
      else
        Optimizer::runMem2Reg( CGF.M );

      /* Get the name of the output file. */
      std::string outname( name );
      {
        size_t pos = outname.rfind( "." );
        if ( pos == std::string::npos )
          outname += ".ll";
        else
          outname.replace( pos, outname.length(), ".ll" );
      }

      /* Write the module to the output file. */
      std::string errorStr;
      raw_fd_ostream stream( outname.c_str(), errorStr );
      CGF.M.print( stream, NULL );

      delete lexer;
    }

    if ( symbols )
    {
      std::cout
        << Symbol::size() - Token::KeywordsTable.size() - 1 /* empty symbol */
        << " symbols created\n";
      if ( TypeFactory::sizeP() )
        std::cout << TypeFactory::sizeP() << " pointer types created\n";
      if ( TypeFactory::sizeF() )
        std::cout << TypeFactory::sizeF() << " function types created\n";
    }

    Symbol::destroy();
    TypeFactory::destroy();
  }

  return printDiagnosticSummary();
}
