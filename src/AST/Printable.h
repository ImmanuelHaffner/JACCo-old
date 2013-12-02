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
    /// \brief Holds properties necessary for pretty-printing.
    struct Printer
    {
      std::ostream &out;
      char indent;
    };

    ///
    struct Printable
    {
<<<<<<< HEAD
      virtual void print( Printer const p ) = 0;
||||||| merged common ancestors
      virtual void print() = 0;
=======
      virtual void print() const = 0;
>>>>>>> stuff
    }; // end struct Printable
  } // end namespace AST
} // end namespace C4

#endif
