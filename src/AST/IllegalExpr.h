//===--- IllegalExpr.h ----------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_ILLEGAL_EXPR_H
#define C4_ILLEGAL_EXPR_H

#include <iostream>
#include "Expr.h"


namespace C4
{
  namespace AST
  {
    ///
    struct IllegalExpr : Expr
    {
      IllegalExpr( Lex::Token const &tok ) : Expr(tok) {}
      virtual ~IllegalExpr() {}

      friend std::ostream & operator<<( std::ostream &out,
          IllegalExpr const &expr );
    }; // end struct IllegalExpression

    std::ostream & operator<<( std::ostream &out, IllegalExpr const &expr );
  } // end namespace AST
} // end namespace C4

#endif
