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
    struct DirectDeclarator;
    struct Declarator : Locatable
    {
      Declarator( Lex::Token const &tok, size_t const pointerCount,
          DirectDeclarator const * const directDeclarator )
        : Locatable (tok), pointerCount(pointerCount),
        directDeclarator(directDeclarator)
      {}

      virtual ~Declarator() {}

      void print( Printer const p ) const;

      size_t const pointerCount;
      DirectDeclarator const * const directDeclarator;
    }; // end struct Declarator


    /// Illegal Declarator
    struct IllegalDeclarator : Declarator
    {
      IllegalDeclarator( Lex::Token const &tok ) : Declarator(tok,0,NULL) {}
      ~IllegalDeclarator() {}

      void print( Printer const p ) const;
    }; // end struct IllegalDeclarator


    /// Direct Declarator
    struct DirectDeclarator : Locatable
    {
      DirectDeclarator( Lex::Token const &tok )
        : Locatable(tok), declarator(NULL), directDeclarator(NULL), params(NULL)
      {}

      DirectDeclarator( Lex::Token const &tok,
          Declarator const * const declarator,
          ParamList const * const params = NULL )
        : Locatable(tok), declarator(nonNull(declarator)),
        directDeclarator(NULL), params(params)
      {}

      DirectDeclarator( Lex::Token const &tok,
          DirectDeclarator const * const directDeclarator,
          ParamList const * const params = NULL )
        : Locatable(tok), declarator(NULL),
        directDeclarator(nonNull(directDeclarator)), params(params)
      {}

      DirectDeclarator( Lex::Token const &tok, ParamList const * const params )
        : Locatable(tok), declarator(NULL), directDeclarator(NULL),
        params(nonNull(params))
      {}

      ~DirectDeclarator() {}

      void print( Printer const p ) const;

      Declarator const * const declarator;
      DirectDeclarator const * const directDeclarator;
      ParamList const * const params;
    }; // end struct DirectDeclarator


    /// Struct Declarator List
    struct StructDeclaratorList : List< Declarator >
    {
      ~StructDeclaratorList() {}
      void print( Printer const p ) const;
    }; // end struct StructDeclaratorList


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
  } // end namespace AST
} // end namespace C4

#endif
