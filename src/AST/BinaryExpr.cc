//===--- BinaryExpr.cc ----------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#include "BinaryExpr.h"


using namespace C4;
using namespace AST;


std::ostream & AST::operator<<( std::ostream &out, BinaryExpr const &expr )
{
  (void) expr; // suppress unused parameter warning
  out << "binary expression";
  return out;
}

void BinaryExpr::print() {
    stdout << lhs.print() << " " << token.sym.str() << " " << rhs.print();
