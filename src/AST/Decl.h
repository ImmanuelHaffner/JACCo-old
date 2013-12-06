///===--- Decl.h ----------------------------------------------------------===//
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
#include "List.h"
#include "../util.h"
#include <vector>

namespace C4
{
  namespace AST
  {
    // Forward declarations
    struct TypeSpecifier;

    /// External Declaration
    struct ExtDecl : Locatable
    {
      ExtDecl( Lex::Token const &tok ) : Locatable(tok) {}
      virtual ~ExtDecl() {}

      void print( Printer const p ) const;
    }; // end struct ExtDecl

    /// Illegal External Declaration
    struct IllegalExtDecl : ExtDecl
    {
      IllegalExtDecl( Lex::Token const &tok ) : ExtDecl(tok) {}
      ~IllegalExtDecl() {}

      void print( Printer const p ) const;
    }; // end struct IllegalExtDecl

    /// Declaration
    struct Declarator;
    struct Decl : ExtDecl
    {
      Decl( Lex::Token const &tok, TypeSpecifier const * const typeSpec,
          Declarator const * const declarator = NULL )
        : ExtDecl(tok), typeSpec(nonNull(typeSpec)), declarator(declarator)
      {}

      virtual ~Decl() {}

      TypeSpecifier const * const typeSpec;
      Declarator const * const declarator;
    }; // end struct Declaration

    /// Illegal Declaration
    struct IllegalDecl : Decl
    {
      IllegalDecl( Lex::Token const &tok ) : Decl(tok, NULL, NULL) {}
      ~IllegalDecl() {}

      void print( Printer const p ) const;
    }; // end struct IllegalDecl

    /// Struct Declaration List
    struct StructDecl;
    struct StructDeclList : List< StructDecl >
    {
      ~StructDeclList() {}

      void print( Printer const p );
    }; // end struct StructDeclList

    /// Struct Declaration
    struct StructDeclaratorList;
    struct StructDecl
    {
      StructDecl( TypeSpecifier const * const typeSpec,
          StructDeclaratorList const * const structDeclarators )
        : typeSpec(nonNull(typeSpec)),
        structDeclarators(nonNull(structDeclarators))
      {}

      TypeSpecifier const * const typeSpec;
      StructDeclaratorList const * const structDeclarators;
    }; // end struct StructDecl

    /// Declarator
    struct Declarator : Locatable
    {
      Declarator( Lex::Token const &tok ) : Locatable (tok) {}
      virtual ~Declarator() {}

      void print( Printer const p ) const;
    }; // end struct Declarator

    /// Illegal Declarator
    struct IllegalDeclarator : Declarator
    {
      IllegalDeclarator( Lex::Token const &tok ) : Declarator(tok) {}
      ~IllegalDeclarator() {}

      void print( Printer const p ) const;
    }; // end struct IllegalDeclarator

    /// Declaration List
    struct DeclList : List< Decl >
    {
      ~DeclList() {}
    }; // end struct DeclList

    /// Function Definition
    struct FunctionDef : ExtDecl
    {
      FunctionDef( Lex::Token const &tok, TypeSpecifier const * typeSpec,
          Declarator const * declarator, DeclList const * declList,
          CompoundStmt const * cStmt ) :
        ExtDecl(tok), typeSpec(typeSpec), declarator(declarator),
        declList(declList), cStmt(cStmt) {}

      virtual ~FunctionDef() {}

      void print( Printer const p ) const;
      TypeSpecifier const * typeSpec;
      Declarator const * declarator;
      DeclList const * declList;
      CompoundStmt const * cStmt;
    }; // end struct FunctionDef

    /// Illegal Function Definition
    struct IllegalFunctionDef : FunctionDef
    {
      IllegalFunctionDef( Lex::Token const &tok ) :
        FunctionDef(tok, NULL, NULL, NULL, NULL ) {}
      ~IllegalFunctionDef() {}

      void print( Printer const p ) const;
    }; // end struct IllegalFunctionDef
  } // end namespace AST
} // end namespace C4

#endif
