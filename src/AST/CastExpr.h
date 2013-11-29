//===--- CastExpr.h -------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_CAST_EXPR_H
#define C4_CAST_EXPR_H

#include <iostream>
#include "Expr.h"
#include "../Lex/Token.h"

namespace C4
{
  namespace AST
  {
    ///
    struct CastExpr : Expr
    {
      CastExpr( Lex::Token const &tok, Expr const &expr ) :
        Expr(tok), expr(expr) {}
      virtual ~CastExpr() {}

      friend std::ostream & operator<<( std::ostream &out,
          CastExpr const &expr );

      // TODO type
      Expr const &expr;
    }; // end struct CastExpr

    std::ostream & operator<<( std::ostream &out, CastExpr const &expr );
  } // end namespace AST
} // end namespace C4

#endif
