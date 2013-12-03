//===--- Decl.h -----------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the Abstract Syntax tree interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_DECL_H
#define C4_DECL_H

#include <iostream>
#include "Locatable.h"
#include "Printable.h"


namespace C4
{
  namespace AST
  {
    /// Declaration
    struct Decl : Locatable, Printable
    {
      Decl( Lex::Token const &tok ) : Locatable(tok) {}
      virtual ~Decl() {}
    }; // end struct Declaration

    /// Illegal Declaration
    struct IllegalDecl : Decl
    {
      IllegalDecl( Lex::Token const &tok ) : Decl(tok) {}
      virtual ~IllegalDecl() {}

      void print( Printer const p ) const;
    }; // end struct IllegalDeclaration
  } // end namespace AST
} // end namespace C4

#endif
