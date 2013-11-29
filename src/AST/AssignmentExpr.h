//===--- AssignmentExpr.h -------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_ASSIGNMENT_EXPR_H
#define C4_ASSIGNMENT_EXPR_H

#include <iostream>
#include "Expr.h"
#include "../Lex/Token.h"


namespace C4
{
  namespace AST
  {
    ///
    struct AssignmentExpr : Expr
    {
      AssignmentExpr( Lex::Token const op, Expr &lhs, Expr &rhs );
      virtual ~AssignmentExpr() {}

      Expr & getLHS() { return lhs; }
      Expr & getRHS() { return rhs; }
      Lex::Token getOperator() { return op; }
      friend std::ostream & operator<<( std::ostream &out,
          AssignmentExpr const &expr );

      Lex::Token const op;

      private:
      Expr &lhs;
      Expr &rhs;
    }; // end struct AssignmentExpr

    std::ostream & operator<<( std::ostream &out,
        AssignmentExpr const &expr );
  } // end namespace AST
} // end namespace C4

#endif
