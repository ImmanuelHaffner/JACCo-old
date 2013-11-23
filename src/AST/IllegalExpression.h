//===--- IllegalExpression.h ----------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_ILLEGAL_EXPRESSION_H
#define C4_ILLEGAL_EXPRESSION_H

#include <iostream>
#include "Expression.h"


namespace C4
{
  namespace AST
  {
    ///
    struct IllegalExpression : Expression
    {
      IllegalExpression() {}
      virtual ~IllegalExpression() {}

      friend std::ostream & operator<<( std::ostream &out,
          IllegalExpression const &expr );
    }; // end struct IllegalExpression

    std::ostream & operator<<( std::ostream &out,
        IllegalExpression const &expr );
  } // end namespace AST
} // end namespace C4

#endif
