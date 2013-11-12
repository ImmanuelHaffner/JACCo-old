//===--- AST.cc -----------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements the Abstract Syntax tree interface.
//
//===----------------------------------------------------------------------===//

#include "AST.h"

using namespace C4;
using namespace Parse;

AST::AST( AST * const parent ) : parent(parent) {}

AST::~AST()
{
  for ( auto it = childs.begin(); it != childs.end(); ++it )
  {
    delete (*it);
  }
}

AST * AST::getParent() const
{
  return parent;
}

void AST::setParent( AST * p )
{
  this->parent = p;
}

AST * AST::getChild( int n ) const
{
  return childs[n];
}

void AST::setChild( AST * c, int n )
{
  childs[n] = c;
}

std::vector< AST * > AST::getChilds()
{
  return std::vector< AST *>( childs );
}

std::ostream & Parse::operator<<( std::ostream &out, AST const &node )
{
  out << "AST Node";
  return out;
}

void AST::dump() const
{
  std::cout << *this;
}
