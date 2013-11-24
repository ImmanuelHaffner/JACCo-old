//===--- PostfixExpression.h ----------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_POSTFIX_EXPRESSION_H
#define C4_POSTFIX_EXPRESSION_H

#include <iostream>
#include "Expression.h"
#include "../Lex/Token.h"

namespace C4
{
  namespace AST
  {
    ///
    struct PostfixExpression : Expression
    {
      PostfixExpression( Lex::Token const op, Expression &expr );
      virtual ~PostfixExpression() {}

      Expression & getSubExpr() { return expr; }
      friend std::ostream & operator<<( std::ostream &out,
          PostfixExpression const &expr );

      Lex::Token const op;

      private:
      Expression &expr;
    }; // end struct PostfixExpression

    std::ostream & operator<<( std::ostream &out,
        PostfixExpression const &expr );
  } // end namespace AST
} // end namespace C4

#endif
