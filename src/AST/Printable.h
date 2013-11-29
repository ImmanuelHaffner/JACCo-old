//===--- Printable.h -----------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_PRINTABLE_H
#define C4_PRINTABLE_H

#include <iostream>


namespace C4
{
  namespace AST
  {
    ///
    struct Printable
    {
      virtual void print() = 0;
    }; // end struct Printable
  } // end namespace AST
} // end namespace C4

#endif
