//===--- AssignmentExpr.cc ------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#include "AssignmentExpr.h"


using namespace C4;
using namespace AST;


std::ostream & AST::operator<<( std::ostream &out, AssignmentExpr const &expr )
{
  (void) expr; // suppress unused parameter warning
  out << "assignment expression";
  return out;
}
