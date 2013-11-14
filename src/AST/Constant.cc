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

Constant::Constant( Token const &tok, ASTNode * const parent/* = NULL*/ )
  : ASTNode( ASTType::CONSTANT, parent ), tok(tok)
{}

Constant::~Constant() {}

std::ostream & AST::operator<<( std::ostream &out, Constant const &node )
{
  node.dump( out );
  return out;
}

void Constant::dump( std::ostream &out /*= std::cout*/,
    int const n /*= 0*/ ) const
{
  for ( int i = 0; i < n; ++i )
    out << " ";
  out << tok;
}
