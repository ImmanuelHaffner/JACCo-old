//===--- UnaryExpression.cc -----------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#include "UnaryExpression.h"


using namespace C4;
using namespace AST;


UnaryExpression::UnaryExpression( Lex::Token const op, Expression &expr ) :
  op(op), expr(expr)
{}

std::ostream & AST::operator<<( std::ostream &out, UnaryExpression const &expr )
{
  out << "unary expression " << expr.op.kind << " " << expr.expr;
  return out;
}

void UnaryExpression::accept ( ASTNodeVisitor & visitor ) {
    expr.accept ( visitor );
    visitor.visit ( * this );
}
