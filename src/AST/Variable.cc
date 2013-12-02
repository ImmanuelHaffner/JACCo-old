//===--- Variable.cc ------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements the Abstract Syntax tree interface.
//
//===----------------------------------------------------------------------===//

#include "Expr.h"


using namespace C4;
using namespace Lex;
using namespace AST;


std::ostream & AST::operator<<( std::ostream &out, Variable const &var )
{
  out << "Variable " << var.tok.sym;
  return out;
}
