//===--- BinaryExpression.h -----------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_BINARY_EXPRESSION_H
#define C4_BINARY_EXPRESSION_H

#include <iostream>
#include "Expression.h"
#include "../Lex/Token.h"


namespace C4
{
  namespace AST
  {
    ///
    struct BinaryExpression : Expression
    {
      BinaryExpression( Lex::Token const op, Expression &lhs,
          Expression &rhs );
      virtual ~BinaryExpression() {}

      Expression & getLHS() { return lhs; }
      Expression & getRHS() { return rhs; }
      friend std::ostream & operator<<( std::ostream &out,
          BinaryExpression const &expr );

      Lex::Token const op;

      private:
      Expression &lhs;
      Expression &rhs;
    }; // end struct BinaryExpression

    std::ostream & operator<<( std::ostream &out,
        BinaryExpression const &expr );
  } // end namespace AST
} // end namespace C4

#endif
