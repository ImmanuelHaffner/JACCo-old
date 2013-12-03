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
    /// Type
    struct Type : Locatable, Printable
    {
      Type( Lex::Token const &tok ) : Locatable(tok) {}
      virtual ~Type() {}
    }; // end struct Type

    /// Illegal Type
    struct IllegalType : Type
    {
      IllegalType( Lex::Token const &tok ) : Type(tok) {}
      virtual ~IllegalType() {}

      void print( Printer const p ) const; 
    }; // end struct IllegalType
  } // end namespace AST
} // end namespace C4

#endif
