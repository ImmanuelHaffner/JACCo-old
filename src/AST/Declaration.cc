//===--- Declaration.cc ---------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements the Abstract Syntax tree interface.
//
//===----------------------------------------------------------------------===//

#include "Declaration.h"


using namespace C4;
using namespace AST;


std::ostream & AST::operator<<( std::ostream &out, Declaration const &decl )
{
  out << "declaration";
  return out;
}
