///===--- Decl.h -----------------------------------------------------------===//
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


namespace C4
{
  namespace AST
  {
    /// Declaration
    struct Decl : Locatable
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

    /// Type Specifier
    struct TypeSpecifier : Locatable
    {
      TypeSpecifier( Lex::Token const &tok, Decl *, Decl * ) : Locatable(tok) {}
      virtual ~TypeSpecifier() {}
      
      void print( Printer const p ) const;
    };

    /// Type Specifier
    struct IllegalTypeSpecifier : TypeSpecifier 
    {
      IllegalTypeSpecifier( Lex::Token const &tok, Decl * a, Decl * b ) :
        TypeSpecifier(tok,a,b) {}
      virtual ~IllegalTypeSpecifier() {}
      
      void print( Printer const p ) const;
    };
      } // end namespace AST
} // end namespace C4

#endif
