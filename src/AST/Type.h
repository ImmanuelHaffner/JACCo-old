//===--- Type.h -----------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the Abstract Syntax tree interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_TYPE_H
#define C4_TYPE_H

#include <iostream>
#include "Locatable.h"
#include "Printable.h"


namespace C4
{
  namespace AST
  {
    ///
    struct Type : Locatable, Printable
    {
      Type( Lex::Token const &tok ) : Locatable(tok) {}
      virtual ~Type() {}

      // TODO implement in sub-classes
      virtual void print( Printer const ) {}

      friend std::ostream & operator<<( std::ostream &out, Type const &decl );
    }; // end struct Type

    std::ostream & operator<<( std::ostream &out, Type const &type );
  } // end namespace AST
} // end namespace C4

#endif
