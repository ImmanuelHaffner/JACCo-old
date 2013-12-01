//===--- IllegalType.cc ---------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#include "IllegalType.h"


using namespace C4;
using namespace AST;


std::ostream & AST::operator<<( std::ostream &out, IllegalType const &expr )
{
  (void) expr; // suppress unused parameter warning
  out << "illegal type";
  return out;
}
