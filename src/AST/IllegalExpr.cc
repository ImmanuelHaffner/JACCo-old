//===--- IllegalExpr.cc ---------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#include "IllegalExpr.h"


using namespace C4;
using namespace AST;


std::ostream & AST::operator<<( std::ostream &out, IllegalExpr const &expr )
{
  (void) expr; // suppress unused parameter warning
  out << "illegal expression";
  return out;
}
