//===--- Visitable.h --------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_VISITABLE_H
#define C4_VISITABLE_H

#include <iostream>


namespace C4
{
  namespace AST
  {
    struct ASTVisitor; // forward-declaration

    ///
    struct Visitable 
    {
      virtual void accept( ASTVisitor &visitor ) = 0;
    };  // end struct Visitable
  } // end namespace AST
} // end namespace C4

#endif
