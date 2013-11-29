//===--- UnaryExpr.h ------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_UNARY_EXPR_H
#define C4_UNARY_EXPR_H

#include <iostream>
#include "Expr.h"
#include "../Lex/Token.h"

namespace C4
{
  namespace AST
  {
    ///
    struct UnaryExpr : Expr
    {
      UnaryExpr( Lex::Token const &tok ) : Expr(tok) {}
      virtual ~UnaryExpr() {}

      friend std::ostream & operator<<( std::ostream &out,
          UnaryExpr const &expr );
    }; // end struct UnaryExpr

    std::ostream & operator<<( std::ostream &out, UnaryExpr const &expr );
  } // end namespace AST
} // end namespace C4

#endif
