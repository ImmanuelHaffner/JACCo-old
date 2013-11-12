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
    struct AST
    {
      AST( AST * const parent = NULL );
      virtual ~AST();

      AST * getParent() const;
      void setParent( AST * p );
      AST * getChild( int n ) const;
      void setChild( AST * c, int n );
      std::vector< AST * > getChilds();

      friend std::ostream & operator<<( std::ostream &out, AST const &node );
      virtual void dump() const;

      private:
      AST * parent;
      std::vector< AST * > childs;
    };
  }
}

#endif
