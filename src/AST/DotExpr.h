//===--- DotExpr.h --------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_DOT_EXPR_H
#define C4_DOT_EXPR_H

#include <iostream>
#include "PostfixExpr.h"
#include "../Lex/Token.h"

namespace C4
{
  namespace AST
  {
    ///
    struct DotExpr : PostfixExpr
    {
      DotExpr( Lex::Token const &tok, Expr const &rhs ) :
        PostfixExpr(tok), rhs(rhs) {}
      ~DotExpr() {}

      friend std::ostream & operator<<( std::ostream &out,
          DotExpr const &expr );

      Expr const &rhs;
    }; // end struct SubscriptExpr

    std::ostream & operator<<( std::ostream &out, DotExpr const &expr );
  } // end namespace AST
} // end namespace C4

#endif
