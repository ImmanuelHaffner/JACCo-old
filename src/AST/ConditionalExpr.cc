//===--- ConditionalExpr.cc -----------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#include "ConditionalExpr.h"


using namespace C4;
using namespace AST;


ConditionalExpr::ConditionalExpr( Lex::Token const &tok, Expr const &cond,
    Expr const &lhs, Expr const &rhs ) :
  Expr(tok), cond(cond), lhs(lhs), rhs(rhs)
{}

std::ostream & AST::operator<<( std::ostream &out, ConditionalExpr const &expr )
{
  (void) expr; // suppress unused parameter warning
  out << "conditional expression";
  return out;
}
