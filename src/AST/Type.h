//===--- Type.h -----------------------------------------------------------===//
//
//  ~~~ The C4 Compiler ~~~
//
//  This file defines the Abstract Syntax tree interface.
//
//===----------------------------------------------------------------------===//


#ifndef C4_TYPE_H
#define C4_TYPE_H


#include <iostream>
#include "../util.h"
#include "Locatable.h"
#include "../Sema/Env.h"


namespace C4
{
  namespace AST
  {
    // Forward Declarations
    struct StructDeclList;
    struct Declarator;



    /// Type Name
    struct TypeSpecifier;
    struct TypeName : Locatable
    {
      TypeName( Lex::Token const &tok, TypeSpecifier const * const typeSpec,
          Declarator const * const declarator = NULL )
        : Locatable(tok), typeSpec(nonNull(typeSpec)), declarator(declarator)
      {}

      ~TypeName() {}

      void print( Printer const p ) const;

      TypeSpecifier const * const typeSpec;
      Declarator const * const declarator;
    }; // end struct TypeName


    /// Type Specifier
    struct StructSpecifier;
    struct TypeSpecifier : Locatable
    {
      TypeSpecifier( Lex::Token const &tok ) : Locatable(tok) {}
      virtual ~TypeSpecifier() {}

      void print( Printer const p ) const;
      virtual Sema::Type const * analyze( Sema::Env &env ) const;
    }; // end struct TypeSpecifier


    /// Illegal Type Specifier
    struct IllegalTypeSpecifier : TypeSpecifier
    {
      IllegalTypeSpecifier( Lex::Token const &tok ) : TypeSpecifier(tok) {}
      ~IllegalTypeSpecifier() {}

			void print( Printer const p ) const;
      Sema::Type const * analyze( Sema::Env &env ) const;
		}; // end struct TypeSpecifier


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

			void print( Printer const p ) const;
      Sema::Type const * analyze( Sema::Env &env ) const;

			Lex::Token const * const name;
			StructDeclList const * const structDecls;
		}; // end struct StructSpecifier
	} // end namespace AST
} // end namespace C4


#endif
