//===--- Printable.h ------------------------------------------------------===//
//
//  ~~~ The C4 Compiler ~~~
//
//  This file defines the Abstract Syntax Tree interface.
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
      explicit Printer( std::ostream &out, unsigned indent = 0 ) :
        out(out), indent(indent) {}
      std::ostream &out;
      unsigned indent;

      std::ostream & iout() const;
    };

    ///
    struct Printable
    {
      virtual void print( Printer const p ) const = 0;
      void dump() const;
    }; // end struct Printable

    std::ostream & operator<<( std::ostream &out, AST::Printable const &p );
    std::ostream & operator<<( std::ostream &out,
        AST::Printable const * const p );
    std::ostream & operator<<( std::ostream &out, AST::Printer const &p );
    std::ostream & operator<<( std::ostream &out,
        AST::Printer const * const p );
  } // end namespace AST
} // end namespace C4

#endif
