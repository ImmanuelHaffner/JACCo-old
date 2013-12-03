//===--- IllegalDeclaration.cc --------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#include "Decl.h"


using namespace C4;
using namespace AST;


std::ostream & AST::operator<<( std::ostream &out,
    IllegalDeclaration const &decl )
{
  (void) decl; // suppress unused parameter warning
  out << "illegal declaration";
  return out;
}
