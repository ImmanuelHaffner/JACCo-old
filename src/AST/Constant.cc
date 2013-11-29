//===--- Constant.cc ------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements the Abstract Syntax tree interface.
//
//===----------------------------------------------------------------------===//

#include "Constant.h"


using namespace C4;
using namespace Lex;
using namespace AST;


std::ostream & AST::operator<<( std::ostream &out, Constant const &con )
{
  out << "Constant " << con.tok.sym;
  return out;
}
