//===--- Locatable.cc -----------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#include "Locatable.h"


using namespace C4;
using namespace AST;


std::ostream & AST::operator<<( std::ostream &out, Locatable const &loc )
{
  out << loc.tok;
  return out;
}
