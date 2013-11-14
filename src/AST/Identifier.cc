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

Identifier::Identifier( Token const &tok, ASTNode * const parent/* = NULL*/ )
  : ASTNode( ASTType::IDENTIFIER, parent ), tok(tok)
{}

Identifier::~Identifier() {}

std::ostream & AST::operator<<( std::ostream &out, Identifier const &node )
{
  node.dump( out );
  return out;
}

void Identifier::dump( std::ostream &out /*= std::cout*/,
    int const n /*= 0*/ ) const
{
  for ( int i = 0; i < n; ++i )
    out << " ";
  out << tok;
}
