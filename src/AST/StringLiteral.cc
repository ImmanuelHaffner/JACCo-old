//===--- StringLiteral.cc -------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements the Abstract Syntax tree interface.
//
//===----------------------------------------------------------------------===//

#include "StringLiteral.h"

using namespace C4;
using namespace AST;
using namespace Lex;

StringLiteral::StringLiteral( Token &token,
    ASTNode * const parent/* = NULL*/ )
  : ASTNode( ASTType::STRING_LITERAL, parent ), token( token )
{}

StringLiteral::~StringLiteral() {}

std::ostream & AST::operator<<( std::ostream &out, StringLiteral const &node )
{
  out << "StringLiteral " << node.token.text;
  return out;
}

void StringLiteral::dump() const
{
  std::cout << *this;
}
