#include <stdexcept>
#include <iostream>
#include <sstream>

#include "diagnostic.h"
#include "util.h"
#include "Lex/Lexer.h"
#include "Support/CharUtils.h"
#include "Support/Diagnostic.h"


using namespace C4;
using namespace Lex;

enum class Mode {
  TOKENIZE,
  PARSE,
  PRINT_AST,
  COMPILE,
};

int main(int, char** const argv)
{
  try {
    char** i = argv + 1;

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
      for (; char const *name = *i; ++i) {
        FILE* f;
        if (strEq(name, "-")) {
          f    = stdin;
          name = "<stdin>";
        } else {
          f = fopen(name, "rb");
          if (!f)
            errorErrno(Pos(name));
          fclose( f );
        }

        if (hasNewErrors())
          continue;

        switch (mode) {
          case Mode::TOKENIZE:
            {
              C4::Lex::Lexer * lex;
              if ( f == stdin )
                lex = new Lexer;
              else
                lex = new Lexer( name );
              C4::Lex::Lexer lexer( *lex );
              delete lex;

              while ( true )
              {
                Token const & tok = lexer.get();
                if ( tok.kind == TokenKind::END_OF_FILE )
                  break;


                if ( tok.kind == TokenKind::ILLEGAL )
								{
									std::ostringstream oss;
									oss << tok;
									errorf( tok.pos, "%s", oss.str().c_str() );
								}
                else
                  std::cout << tok << std::endl;
              }
              break;
            }

          case Mode::PARSE:
            {}
          case Mode::PRINT_AST:
            {}
          case Mode::COMPILE:
            {
              PANIC("TODO implement");
            }
        }
        //fclose ( f );
      }
    }
  } catch (std::exception const& e) {
    errorf("caught exception: %s", e.what());
  } catch (...) {
    errorf("caught unknown exception");
  }

  return printDiagnosticSummary();
}
