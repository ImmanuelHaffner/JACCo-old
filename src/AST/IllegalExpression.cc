//===--- IllegalExpression.cc ---------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#include "IllegalExpression.h"


using namespace C4;
using namespace AST;


std::ostream & AST::operator<<( std::ostream &out,
    IllegalExpression const &expr )
{
  out << "illegal expression";
  return out;
}
