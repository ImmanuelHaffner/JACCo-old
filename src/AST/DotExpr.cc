//===--- DotExpr.cc -------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#include "Expr.h"


using namespace C4;
using namespace AST;


std::ostream & AST::operator<<( std::ostream &out, DotExpr const &expr )
{
  (void) expr; // suppress unused parameter warning
  out << "dot expression";
  return out;
}
