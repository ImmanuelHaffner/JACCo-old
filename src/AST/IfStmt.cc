//===--- IfStmt.cc ----------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#include "Stmt.h"


using namespace C4;
using namespace AST;


std::ostream & AST::operator<<( std::ostream &out, IfStmt const &stmt )
{
  (void) stmt; // suppress unused parameter warning
  out << "if statement";
  return out;
}
