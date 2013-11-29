//===--- StringLiteral.cc -------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements the Abstract Syntax tree interface.
//
//===----------------------------------------------------------------------===//

#include "StringLiteral.h"


using namespace C4;
using namespace Lex;
using namespace AST;


std::ostream & AST::operator<<( std::ostream &out, StringLiteral const &lit )
{
  out << "StringLiteral " << lit.tok.sym;
  return out;
}
