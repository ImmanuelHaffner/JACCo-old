//===--- PostfixExpr.h ----------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_POSTFIX_EXPR_H
#define C4_POSTFIX_EXPR_H

#include <iostream>
#include "UnaryExpr.h"
#include "../Lex/Token.h"

namespace C4
{
  namespace AST
  {
    ///
    struct PostfixExpr : UnaryExpr
    {
      PostfixExpr( Lex::Token const &tok ) : UnaryExpr(tok) {}
      virtual ~PostfixExpr() {}

      friend std::ostream & operator<<( std::ostream &out,
          PostfixExpr const &expr );
    }; // end struct PostfixExpression

    std::ostream & operator<<( std::ostream &out,
        PostfixExpr const &expr );
  } // end namespace AST
} // end namespace C4

#endif
