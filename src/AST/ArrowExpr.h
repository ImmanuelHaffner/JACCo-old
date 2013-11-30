//===--- ArrowExpr.h ------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_ARROW_EXPR_H
#define C4_ARROW_EXPR_H

#include <iostream>
#include "DotExpr.h"
#include "../Lex/Token.h"

namespace C4
{
  namespace AST
  {
    ///
    struct ArrowExpr : DotExpr
    {
      ArrowExpr( Lex::Token const &tok, Expr const &rhs ) :
        DotExpr(tok, rhs) {}
      ~ArrowExpr() {}

      friend std::ostream & operator<<( std::ostream &out,
          ArrowExpr const &expr );
    }; // end struct SubscriptExpr

    std::ostream & operator<<( std::ostream &out, ArrowExpr const &expr );
  } // end namespace AST
} // end namespace C4

#endif
