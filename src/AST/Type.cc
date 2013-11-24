//===--- Type.cc ----------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements the Abstract Syntax tree interface.
//
//===----------------------------------------------------------------------===//

#include "Type.h"


using namespace C4;
using namespace AST;


std::ostream & AST::operator<<( std::ostream &out, Type const &type )
{
  (void) type; // suppress unused parameter warning
  out << "Type";
  return out;
}
