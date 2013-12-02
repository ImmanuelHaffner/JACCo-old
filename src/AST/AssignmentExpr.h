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
      AssignmentExpr( Lex::Token const & tok, Expr const * const lhs,
					Expr const * const rhs ) :
        BinaryExpr(tok, lhs, rhs) {}

      ~AssignmentExpr() {};
      virtual void print( Printer const ) const;
    }; // end struct AssignmentExpr

    std::ostream & operator<<( std::ostream &out, AssignmentExpr const &expr );
  } // end namespace AST
} // end namespace C4

#endif
