//===--- IllegalStatement.cc ---------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#include "IllegalStatement.h"


using namespace C4;
using namespace AST;


std::ostream & AST::operator<<( std::ostream &out,
    IllegalStatement const &stmt )
{
  (void) stmt; // suppress unused parameter warning
  out << "illegal statement";
  return out;
}
