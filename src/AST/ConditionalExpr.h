//===--- ConditionalExpr.h ------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_CONDITIONAL_EXPR_H
#define C4_CONDITIONAL_EXPR_H

#include <iostream>
#include "Expr.h"
#include "../Lex/Token.h"


namespace C4
{
  namespace AST
  {
    ///
    struct ConditionalExpr : Expr
    {
      ConditionalExpr( Lex::Token const &tok, Expr const * const cond,
          Expr const * const lhs, Expr const * const rhs ) :
				Expr(tok), cond(cond), lhs(lhs), rhs(rhs) {}
      ~ConditionalExpr() {}

      friend std::ostream & operator<<( std::ostream &out,
          ConditionalExpr const &expr );

      Expr const * const cond;
      Expr const * const lhs;
      Expr const * const rhs;
      void print( Printer const ) const;

    }; // end struct ConditionalExpr

    std::ostream & operator<<( std::ostream &out, ConditionalExpr const &expr );
  } // end namespace AST
} // end namespace C4

#endif
