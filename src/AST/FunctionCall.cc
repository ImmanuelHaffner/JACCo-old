//===--- FunctionCall.cc --------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#include "Expr.h"


using namespace C4;
using namespace AST;


std::ostream & AST::operator<<( std::ostream &out, FunctionCall const &expr )
{
  (void) expr; // suppress unused parameter warning
  out << "signature expression";
  return out;
}
