//===--- Constant.cc ------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements the Abstract Syntax tree interface.
//
//===----------------------------------------------------------------------===//

#include "Constant.h"

using namespace C4;
using namespace AST;
using namespace Lex;

Constant::Constant( ConstantToken &token,
    ASTNode * const parent/* = NULL*/ )
  : ASTNode( ASTType::PRIMARY_EXPRESSION, parent ), token( token )
{}

Constant::~Constant() {}

std::ostream & AST::operator<<( std::ostream &out, Constant const &node )
{
  out << "Constant " << node.token.text;
  return out;
}

void Constant::dump() const
{
  std::cout << *this;
}
