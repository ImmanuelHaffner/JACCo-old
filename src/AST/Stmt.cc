//===--- Stmt.cc -----------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements the Abstract Syntax tree interface.
//
//===----------------------------------------------------------------------===//

#include "Stmt.h"


using namespace C4;
using namespace AST;


std::ostream & AST::operator<<( std::ostream &out, Stmt const &stmt )
{
  (void) stmt; // suppress unused parameter warning
  out << "statement";
  return out;
}
