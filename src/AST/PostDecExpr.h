//===--- PostDecExpr.h -----------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_POST_DEC_EXPR_H
#define C4_POST_DEC_EXPR_H

#include <iostream>
#include "PostfixExpr.h"
#include "../Lex/Token.h"

namespace C4
{
  namespace AST
  {
    ///
    struct PostDecExpr : PostfixExpr
    {
      PostDecExpr( Lex::Token const &tok, Expr const &expr ) :
        PostfixExpr(tok), expr(expr) {}
      ~PostDecExpr() {}

      friend std::ostream & operator<<( std::ostream &out,
          PostDecExpr const &expr );

      Expr const &expr;
    }; // end struct PostDecExpr

    std::ostream & operator<<( std::ostream &out, PostDecExpr const &expr );
  } // end namespace AST
} // end namespace C4

#endif
