//===--- PostIncExpr.cc ----------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#include "PostIncExpr.h"


using namespace C4;
using namespace AST;


std::ostream & AST::operator<<( std::ostream &out, PostIncExpr const &expr )
{
  (void) expr; // suppress unused parameter warning
  out << "post-increment expression";
  return out;
}
