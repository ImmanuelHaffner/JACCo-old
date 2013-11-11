//===--- AST.h ------------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the Abstract Syntax tree interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_AST_H
#define C4_AST_H

#include <vector>
#include <iostream>

namespace C4
{
  namespace Parse
  {
    struct ASTNode
    {
      ASTNode( ASTNode * const parent = NULL );
      virtual ~ASTNode();

      ASTNode * getParent() const;
      void setParent( ASTNode * p );
      ASTNode * getChild( int n ) const;
      void setChild( ASTNode * c, int n );
      std::vector< ASTNode * > getChilds();

      friend std::ostream & operator<<( std::ostream &out, ASTNode const &node );
      virtual void dump() const;

      private:
      ASTNode * parent;
      std::vector< ASTNode * > childs;
    };
  }
}

#endif
