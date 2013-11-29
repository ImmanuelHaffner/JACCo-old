//===--- StringLiteral.h --------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_STRING_LITERAL_H
#define C4_STRING_LITERAL_H

#include <iostream>

#include "Expr.h"
#include "../Lex/Token.h"


namespace C4
{
  namespace AST
  {
    ///
    struct StringLiteral : Expr
    {
      explicit StringLiteral( Lex::Token const &tok ) : Expr(tok)
      {
        assert( tok.kind == Lex::TK::STRING_LITERAL
            && "token must be a string-literal" );
      }

      ~StringLiteral() {}

      friend std::ostream & operator<<( std::ostream &out,
          StringLiteral const &lit );
    }; // end struct Variable

    std::ostream & operator<<( std::ostream &out, StringLiteral const &lit );
  } // end namespace AST
} // end namespace C4

#endif
