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
    struct ExtDecl : Printable
    {
      virtual ~ExtDecl() {}

      virtual void print( Printer const p ) const;
    }; // end struct ExtDecl


    /// Illegal External Declaration
    struct IllegalExtDecl : Locatable, ExtDecl
    {
      IllegalExtDecl( Lex::Token const &tok ) : Locatable(tok) {}
      ~IllegalExtDecl() {}

      void print( Printer const p ) const;
    }; // end struct IllegalExtDecl


    /// Declaration
    struct Declarator;
    struct Decl : ExtDecl
    {
      Decl( TypeSpecifier const * const typeSpec,
          Declarator const * const declarator = NULL )
        : typeSpec(nonNull(typeSpec)), declarator(declarator)
      {}

      virtual ~Decl() {}

      virtual void print( Printer const p ) const;

      TypeSpecifier const * const typeSpec;
      Declarator const * const declarator;
    }; // end struct Declaration


    struct IllegalDecl : Locatable, Decl
    {
      IllegalDecl( Lex::Token const &tok, TypeSpecifier const * const typeSpec )
        : Locatable(tok), Decl(typeSpec) {}
      ~IllegalDecl() {}

      void print( Printer const p ) const;
    }; // end IllegalDecl


    /// Struct Declaration List
    struct StructDecl;
    struct StructDeclList : List< StructDecl >
    {
      ~StructDeclList() {}
      void print( Printer const p ) const;
    }; // end struct StructDeclList

    /// Struct Declaration
    struct StructDeclaratorList;
    struct StructDecl : Decl
    {
      StructDecl( TypeSpecifier const * const typeSpec,
          StructDeclaratorList const * const structDeclarators )
        : Decl(typeSpec), structDeclarators(nonNull(structDeclarators))
      {}

      StructDeclaratorList const * const structDeclarators;
    }; // end struct StructDecl


    /// Parameter Declaration
    struct ParamDecl : Decl
    {
      ParamDecl( TypeSpecifier const * const typeSpec,
          Declarator const * const declarator = NULL )
        : Decl(typeSpec, declarator)
      {}

      ~ParamDecl() {}

      void print( Printer const p ) const;
    }; // end struct ParamDecl


    /// Parameter List
    struct ParamList : List< ParamDecl >
    {
      ~ParamList() {}
      void print( Printer const p ) const;
    }; // end struct ParamList

    /// Declarator
    struct Declarator : Locatable
    {
      Declarator( Lex::Token const &tok ) : Locatable (tok) {}
      virtual ~Declarator() {}

      void print( Printer const p ) const;
    }; // end struct Declarator


    /// Struct Declarator List
    struct StructDeclaratorList : List< Declarator >
    {
      ~StructDeclaratorList() {}
      void print( Printer const p ) const;
    }; // end struct StructDeclaratorList


    /// Illegal Declarator
    struct IllegalDeclarator : Declarator
    {
      IllegalDeclarator( Lex::Token const &tok ) : Declarator(tok) {}
      ~IllegalDeclarator() {}

      void print( Printer const p ) const;
    }; // end struct IllegalDeclarator


    struct DeclaratorList : List< Declarator >
    {
      ~DeclaratorList() {}
      void print( Printer const p ) const;
    }; // end struct DeclaratorList


    /// Declaration List
    struct DeclList : List< Decl >
    {
      ~DeclList() {}
      void print( Printer const p ) const;
    }; // end struct DeclList


    /// Function Definition
    struct FunctionDef : ExtDecl
    {
      FunctionDef( TypeSpecifier const * const typeSpec,
          Declarator const * const declarator, DeclList const * const decls,
          CompoundStmt const * const compStmt )
        : typeSpec(typeSpec), declarator(nonNull(declarator)), decls(decls),
        compStmt(nonNull(compStmt))
      {}

      ~FunctionDef() {}

      void print( Printer const p ) const;

      TypeSpecifier const * const typeSpec;
      Declarator const * const declarator;
      DeclList const * const decls;
      CompoundStmt const * const compStmt;
    }; // end struct FunctionDef


    /// Pointer
    struct Pointer : Declarator
    {
      Pointer( Lex::Token const &tok, size_t starCount,
          Declarator const * const subDec )
        : Declarator(tok), starCount(starCount), subDec(subDec) {}
      ~Pointer() {}

      void print( Printer const p ) const;

      size_t starCount;
      Declarator const * const subDec;
    }; // end struct Pointer

    /// FunctionDeclarator
    struct FunctionDeclarator : Declarator
    {
      FunctionDeclarator( Lex::Token const &tok,
          Declarator const * const subDec, ParamList const * const paramList )
        : Declarator(tok), subDec(subDec), paramList(paramList) {}
      ~FunctionDeclarator() {}

      void print( Printer const p ) const;

      Declarator const * const subDec;
      ParamList const * const paramList;
    }; // end struct FunctionDeclarator

    struct Identifier : Declarator
    {
      Identifier( Lex::Token const &tok ) : Declarator(tok) {}
      ~Identifier() {}

      void print( Printer const p ) const;
    }; // end struct Identifier
  } // end namespace AST
} // end namespace C4

#endif
