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
#include "BinaryExpr.h"
#include "../Lex/Token.h"


namespace C4
{
  namespace AST
  {
    ///
    struct AssignmentExpr : BinaryExpr
    {
      AssignmentExpr( Lex::Token const op, Expr const &lhs, Expr const &rhs ) :
        BinaryExpr(op, lhs, rhs) {}

      ~AssignmentExpr() {}
    }; // end struct AssignmentExpr

    std::ostream & operator<<( std::ostream &out, AssignmentExpr const &expr );
  } // end namespace AST
} // end namespace C4

#endif
