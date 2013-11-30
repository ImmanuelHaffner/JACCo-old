//===--- PostIncExpr.h -----------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_POST_INC_EXPR_H
#define C4_POST_INC_EXPR_H

#include <iostream>
#include "PostfixExpr.h"
#include "../Lex/Token.h"

namespace C4
{
  namespace AST
  {
    ///
    struct PostIncExpr : PostfixExpr
    {
      PostIncExpr( Lex::Token const &tok, Expr const &expr ) :
        PostfixExpr(tok), expr(expr) {}
      ~PostIncExpr() {}

      friend std::ostream & operator<<( std::ostream &out,
          PostIncExpr const &expr );

      Expr const &expr;
    }; // end struct PostIncExpr

    std::ostream & operator<<( std::ostream &out, PostIncExpr const &expr );
  } // end namespace AST
} // end namespace C4

#endif
