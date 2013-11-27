//===--- UnaryExpression.h ------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_UNARY_EXPRESSION_H
#define C4_UNARY_EXPRESSION_H

#include <iostream>
#include "Expression.h"
#include "../Lex/Token.h"

namespace C4
{
  namespace AST
  {
    ///
    struct UnaryExpression : Expression
    {
      UnaryExpression( Lex::Token const op, Expression &expr );
      virtual ~UnaryExpression() {}

      Expression & getSubExpr() { return expr; }
      friend std::ostream & operator<<( std::ostream &out,
          UnaryExpression const &expr );

      Lex::Token const op;
    void accept ( ASTNodeVisitor & visitor );
      private:
      Expression &expr;
    }; // end struct UnaryExpression

    std::ostream & operator<<( std::ostream &out, UnaryExpression const &expr );
  } // end namespace AST
} // end namespace C4

#endif
