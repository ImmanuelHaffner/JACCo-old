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

StringLiteral::StringLiteral( Token const &tok,
    ASTNode * const parent/* = NULL*/ )
  : ASTNode( ASTType::STRING_LITERAL, parent ), tok(tok)
{}

StringLiteral::~StringLiteral() {}

std::ostream & AST::operator<<( std::ostream &out, StringLiteral const &node )
{
  node.dump( out );
  return out;
}

void StringLiteral::dump( std::ostream &out /*= std::cout*/,
    int const n /*= 0*/ ) const
{
  for ( int i = 0; i < n; ++i )
    out << " ";
  out << tok;
}
