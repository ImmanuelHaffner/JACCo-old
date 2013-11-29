//===--- Constant.h -------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_CONSTANT_H
#define C4_CONSTANT_H

#include <iostream>

#include "Expr.h"
#include "../Lex/Token.h"


namespace C4
{
  namespace AST
  {
    ///
    struct Constant : Expr
    {
      explicit Constant( Lex::Token const &tok ) : Expr(tok)
      {
        assert( tok.kind == Lex::TK::CONSTANT && "token must be a constant" );
      }

      ~Constant() {}

      friend std::ostream & operator<<( std::ostream &out,
          Constant const &con );
    }; // end struct Variable

    std::ostream & operator<<( std::ostream &out, Constant const &con );
  } // end namespace AST
} // end namespace C4

#endif
