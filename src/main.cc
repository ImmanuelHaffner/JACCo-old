#include <stdexcept>
#include <iostream>
#include <sstream>

#include "diagnostic.h"
#include "util.h"
#include "Lex/Lexer.h"
#include "Parse/Parser.h"
#include "AST/Printable.h"
#include "Sema/TypeFactory.h"


using namespace C4;
using namespace Lex;
using namespace Parse;
using namespace AST;
using namespace Sema;


enum class Mode {
  TOKENIZE,
  PARSE,
  PRINT_AST,
  COMPILE,
};

int main(int, char** const argv)
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
    for (; char const *name = *i; ++i) {
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

      Lexer * lexer;
      if ( f == stdin )
        lexer = new Lexer;
      else
        lexer = new Lexer( name );

      Parser parser( *lexer );

      switch (mode) {
        case Mode::TOKENIZE:
          {
            while ( true )
            {
              Token const tok = lexer->getToken();
              if ( tok.kind == TK::END_OF_FILE )
                break;
              std::cout << tok.pos << " " << tok << "\n";
            }
          }
          break;

        case Mode::PARSE:
          parser.parse();
          break;

        case Mode::PRINT_AST:
          {
            TranslationUnit const * const unit = parser.parse();
            unit->print( Printer ( std::cout ) );
          }
          break;

        case Mode::COMPILE:
          {
            PANIC("TODO implement");
          }
      }
      //fclose ( f );
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
