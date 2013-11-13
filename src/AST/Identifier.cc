//===--- Identifier.cc ----------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements the Abstract Syntax tree interface.
//
//===----------------------------------------------------------------------===//

#include "Identifier.h"

using namespace C4;
using namespace AST;
using namespace Lex;

Identifier::Identifier( Token &token,
    ASTNode * const parent/* = NULL*/ )
  : ASTNode( ASTType::IDENTIFIER, parent ), token( token )
{}

Identifier::~Identifier() {}

std::ostream & AST::operator<<( std::ostream &out, Identifier const &node )
{
  out << "Identifier " << node.token.text;
  return out;
}

void Identifier::dump() const
{
  std::cout << *this;
}
