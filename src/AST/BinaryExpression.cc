//===--- BinaryExpression.cc ----------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#include "BinaryExpression.h"


using namespace C4;
using namespace AST;


BinaryExpression::BinaryExpression( Expression &lhs, Expression &rhs )
  : lhs(lhs), rhs(rhs)
{}

std::ostream & AST::operator<<( std::ostream &out,
    BinaryExpression const &expr )
{
  out << "binary expression";
  return out;
}
