//===--- SizeofExpr.cc ----------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#include "SizeofExpr.h"


using namespace C4;
using namespace AST;


std::ostream & AST::operator<<( std::ostream &out, SizeofExpr const &expr )
{
  (void) expr; // suppress unused parameter warning
  out << "sizeof expression";
  return out;
}
