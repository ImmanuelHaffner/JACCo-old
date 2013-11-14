//===--- AST.cc -----------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements the Abstract Syntax tree interface.
//
//===----------------------------------------------------------------------===//

#include "AST.h"


using namespace C4;
using namespace AST;
using namespace Lex;

ASTNode::ASTNode( ASTType type, ASTNode * const parent )
  : type(type), parent(parent) {}

ASTNode::~ASTNode()
{
  for ( auto it = childs.begin(); it != childs.end(); ++it )
  {
    delete (*it);
  }
}

ASTNode * ASTNode::getParent() const
{
  return parent;
}

void ASTNode::setParent( ASTNode * const p )
{
  this->parent = p;
}

ASTNode * ASTNode::getChild( int n ) const
{
  return childs[n];
}

void ASTNode::setChild( ASTNode * const c, int n )
{
  childs[n] = c;
}

void ASTNode::append( ASTNode * const c )
{
  childs.push_back( c );
}

void ASTNode::append( ASTNode &c )
{
  childs.push_back( &c );
  c.setParent( this );
}

ASTNode * ASTNode::operator[]( int n )
{
  return childs[n];
}

std::vector< ASTNode * >::iterator ASTNode::begin()
{
  return childs.begin();
}

std::vector< ASTNode * >::const_iterator ASTNode::begin() const
{
  return childs.begin();
}

std::vector< ASTNode * >::iterator ASTNode::end()
{
  return childs.end();
}

std::vector< ASTNode * >::const_iterator ASTNode::end() const
{
  return childs.end();
}

std::ostream & AST::operator<<( std::ostream &out, ASTNode const &node )
{
  node.dump( out );
  return out;
}

void ASTNode::dump( std::ostream &out /*= std::cout*/, int const n /*= 0*/ ) const
{
  for ( int i = 0; i < n; ++i )
    out << " ";
  out << "-AST Node " << reinterpret_cast< size_t >( this );
}
