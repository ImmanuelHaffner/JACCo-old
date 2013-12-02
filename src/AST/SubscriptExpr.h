//===--- SubscriptExpr.h --------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_SUBSCRIPT_EXPR_H
#define C4_SUBSCRIPT_EXPR_H

#include <iostream>
#include "PostfixExpr.h"
#include "../Lex/Token.h"

namespace C4
{
  namespace AST
  {
    ///
    struct SubscriptExpr : PostfixExpr
    {
      SubscriptExpr( Lex::Token const &tok, Expr const * const expr,
          Expr const *index ) :
        PostfixExpr(tok), expr(expr), index(index) {}
      ~SubscriptExpr() {}

      friend std::ostream & operator<<( std::ostream &out,
          SubscriptExpr const &expr );

      Expr const * const expr;
      Expr const * const index; 
      void print( Printer const p ) const;
    }; // end struct SubscriptExpr

    std::ostream & operator<<( std::ostream &out, SubscriptExpr const &expr );
  } // end namespace AST
} // end namespace C4

#endif
