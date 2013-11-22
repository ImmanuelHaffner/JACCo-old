//===--- UnaryExpression.cc -----------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#include "UnaryExpression.h"


using namespace C4;
using namespace AST;


UnaryExpression::UnaryExpression( Expression &sub ) : subExpr(sub)
{}

std::ostream & AST::operator<<( std::ostream &out, UnaryExpression const &expr )
{
  out << "unary expression";
  return out;
}
