//===--- Declaration.h ----------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the Abstract Syntax tree interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_DECLARATION_H
#define C4_DECLARATION_H

#include <iostream>
#include "ASTNode.h"

namespace C4
{
  namespace AST
  {
    struct ASTNodeVisitor;
    ///
    struct Declaration
    {
      virtual ~Declaration() {}

      friend std::ostream & operator<<( std::ostream &out,
          Declaration const &decl );
      void accept ( ASTNodeVisitor & visitor );
    };

    std::ostream & operator<<( std::ostream &out, Declaration const &decl );
  } // end namespace AST
} // end namespace C4

#endif
