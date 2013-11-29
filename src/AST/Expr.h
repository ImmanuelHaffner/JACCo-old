//===--- Expr.h -----------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_EXPR_H
#define C4_EXPR_H

#include <iostream>
#include "Locatable.h"


namespace C4
{
  namespace AST
  {
    ///
    struct Expr : Locatable
    {
      Expr( Lex::Token const &tok ) : Locatable(tok) {}
      virtual ~Expr() {}

      friend std::ostream & operator<<( std::ostream &out, Expr const &expr );
    }; // end struct Expression

    std::ostream & operator<<( std::ostream &out, Expr const &expr );
  } // end namespace AST
} // end namespace C4

#endif
