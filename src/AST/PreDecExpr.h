//===--- PreDecExpr.h -----------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_PRE_DEC_EXPR_H
#define C4_PRE_DEC_EXPR_H

#include <iostream>
#include "UnaryExpr.h"
#include "../Lex/Token.h"

namespace C4
{
  namespace AST
  {
    ///
    struct PreDecExpr : UnaryExpr
    {
      PreDecExpr( Lex::Token const &tok, Expr const &expr ) :
        UnaryExpr(tok), expr(expr) {}
      ~PreDecExpr() {}

      friend std::ostream & operator<<( std::ostream &out,
          PreDecExpr const &expr );

      Expr const &expr;
    }; // end struct PreDecExpr

    std::ostream & operator<<( std::ostream &out, PreDecExpr const &expr );
  } // end namespace AST
} // end namespace C4

#endif
