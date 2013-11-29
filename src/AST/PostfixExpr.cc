//===--- PostfixExpr.cc ---------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#include "PostfixExpr.h"


using namespace C4;
using namespace AST;


std::ostream & AST::operator<<( std::ostream &out, PostfixExpr const &expr )
{
  (void) expr; // suppress unused parameter warning
  out << "postfix expression";
  return out;
}
