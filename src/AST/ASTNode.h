
//===--- ASTNode.h --------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_ASTNODE_H
#define C4_ASTNODE_H

#include <iostream>
#include "ASTNodeVisitor.h"

namespace C4
{
  namespace AST
  {
    ///
    struct ASTNode 
    {
      virtual void accept ( ASTNodeVisitor & visitor ) = 0;
    }; 

  } // end namespace AST
} // end namespace C4

#endif
