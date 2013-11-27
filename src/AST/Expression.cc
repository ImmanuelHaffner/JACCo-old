//===--- Expression.cc ----------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#include "Expression.h"


using namespace C4;
using namespace AST;


std::ostream & AST::operator<<( std::ostream &out, Expression const &expr )
{
  (void) expr; // suppress unused parameter warning
  out << "expression";
  return out;
}

void Expression::accept ( ASTNodeVisitor & visitor ) {
    visitor.visit ( * this );
}
