//===--- ASTNode.cc -------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements the Abstract Syntax tree interface.
//
//===----------------------------------------------------------------------===//

#include "AST.h"

using namespace C4;
using namespace Parse;

ASTNode::ASTNode( ASTNode * const parent ) : parent(parent) {}

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

void ASTNode::setParent( ASTNode * p )
{
  this->parent = p;
}

ASTNode * ASTNode::getChild( int n ) const
{
  return childs[n];
}

void ASTNode::setChild( ASTNode * c, int n )
{
  childs[n] = c;
}

std::vector< ASTNode * > ASTNode::getChilds()
{
  return std::vector< ASTNode *>( childs );
}

std::ostream & Parse::operator<<( std::ostream &out, ASTNode const &node )
{
  out << "AST Node";
  return out;
}

void ASTNode::dump() const
{
  std::cout << *this;
}
