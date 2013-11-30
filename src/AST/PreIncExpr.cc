//===--- PreIncExpr.cc ----------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#include "PreIncExpr.h"


using namespace C4;
using namespace AST;


std::ostream & AST::operator<<( std::ostream &out, PreIncExpr const &expr )
{
  (void) expr; // suppress unused parameter warning
  out << "pre-increment expression";
  return out;
}
