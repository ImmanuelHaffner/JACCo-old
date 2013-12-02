//===--- ExprList.h -------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_EXPR_LIST_H
#define C4_EXPR_LIST_H

#include <iostream>
#include "Expr.h"
#include "../Lex/Token.h"

namespace C4
{
  namespace AST
  {
    ///
    struct ExprList : Expr
    {
      ExprList( Lex::Token const &tok ) : Expr(tok) {}
      virtual ~ExprList() {}

      friend std::ostream & operator<<( std::ostream &out,
          ExprList const &expr );
    }; // end struct ExprList

    std::ostream & operator<<( std::ostream &out, ExprList const &list );
  } // end namespace AST
} // end namespace C4

#endif
