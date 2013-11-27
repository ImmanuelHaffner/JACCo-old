//===--- PostfixExpression.cc ---------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#include "PostfixExpression.h"


using namespace C4;
using namespace AST;


PostfixExpression::PostfixExpression( Lex::Token const op, Expression &expr ) :
  op(op), expr(expr)
{}

std::ostream & AST::operator<<( std::ostream &out, PostfixExpression const &expr )
{
  out << "postfix expression " << expr.expr << " " << expr.op.kind;
  return out;
}

void PostfixExpression::accept ( ASTNodeVisitor & visitor ) {
    visitor.visit ( * this );
}
