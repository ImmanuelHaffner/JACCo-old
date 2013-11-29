//===--- CastExpr.cc ------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#include "CastExpr.h"


using namespace C4;
using namespace AST;


std::ostream & AST::operator<<( std::ostream &out, CastExpr const &expr )
{
  (void) expr; // suppress unused parameter warning
  out << "cast expression";
  return out;
}
