//===--- UnaryExpression.cc -----------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#include "UnaryExpr.h"


using namespace C4;
using namespace AST;


std::ostream & AST::operator<<( std::ostream &out, UnaryExpr const &expr )
{
  (void) expr; // suppress unused parameter warning
  out << "unary expression";
  return out;
}
