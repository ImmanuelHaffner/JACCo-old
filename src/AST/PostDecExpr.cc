//===--- PostDecExpr.cc ----------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#include "PostDecExpr.h"


using namespace C4;
using namespace AST;


std::ostream & AST::operator<<( std::ostream &out, PostDecExpr const &expr )
{
  (void) expr; // suppress unused parameter warning
  out << "post-decrement expression";
  return out;
}
