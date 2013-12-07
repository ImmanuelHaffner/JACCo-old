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
#include "../util.h"
#include "Locatable.h"


namespace C4
{
  namespace AST
  {
    // Forward Declarations
    struct StructDeclList;


    /// Type
    struct Type : Locatable
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

    /// Type Specifier
    struct StructSpecifier;
    struct TypeSpecifier : Type
    {
      TypeSpecifier( Lex::Token const &tok ) : Type(tok) {}
      virtual ~TypeSpecifier() {}

      void print( Printer const p ) const;
    }; // end struct TypeSpecifier

    /// Illegal Type Specifier
    struct IllegalTypeSpecifier : TypeSpecifier
    {
      IllegalTypeSpecifier( Lex::Token const &tok ) : TypeSpecifier(tok) {}
      ~IllegalTypeSpecifier() {}

      void print( Printer const p ) const;
    }; // end struct IllegalTypeSpecifier

    /// Struct Specifier
    struct StructSpecifier : TypeSpecifier
    {
      StructSpecifier( Lex::Token const &tok, Lex::Token const * const name,
          StructDeclList const * const structDecls = NULL )
        : TypeSpecifier(tok), name(nonNull(name)), structDecls(structDecls)
      {
        assert( tok.kind == Lex::TK::Struct &&
            "struct specifier must start with the keyword 'struct'" );
      }

      StructSpecifier( Lex::Token const &tok, StructDeclList const * const
          structDecls )
        : TypeSpecifier(tok), name(NULL), structDecls(nonNull(structDecls))
      {}

      ~StructSpecifier() {}

      Lex::Token const * const name;
      StructDeclList const * const structDecls;
    }; // end struct StructSpecifier
  } // end namespace AST
} // end namespace C4

#endif
