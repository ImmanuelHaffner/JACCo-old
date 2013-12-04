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
#include <vector>

namespace C4
{
  namespace AST
  {
  /// ExternalDecl
    struct ExternalDecl : Locatable 
    {
      ExternalDecl( Lex::Token const &tok ) :
        Locatable(tok) {}
      virtual ~ExternalDecl() {}
      
      void print( Printer const p ) const;
    };

    /// Illegal Declaration
    struct IllegalExternalDecl : ExternalDecl
    {
      IllegalExternalDecl( Lex::Token const &tok ) : ExternalDecl(tok) {}
      virtual ~IllegalExternalDecl() {}

      void print( Printer const p ) const;
    }; // end struct IllegalDeclaration


    struct Decl;
     /// Type Specifier
    struct TypeSpecifier : Locatable
    {
      TypeSpecifier( Lex::Token const &tok, Decl const *, Decl const * ) : Locatable(tok) {}
      virtual ~TypeSpecifier() {}

      void print( Printer const p ) const;
    };
    
    /// Declarator
    struct Declarator : Locatable 
    {
      Declarator( Lex::Token const &tok ) :
        Locatable (tok) {}
      virtual ~Declarator() {}
      
      void print( Printer const p ) const;
    };
    
    /// Declaration
    struct Decl : ExternalDecl
    {
      Decl( Lex::Token const &tok, TypeSpecifier const * typeSpec,
          Declarator const * declarator )
          : ExternalDecl(tok), typeSpec(typeSpec), declarator(declarator)  {}
      virtual ~Decl() {}
      TypeSpecifier const * typeSpec;
      Declarator const * declarator;
    }; // end struct Declaration

    /// Illegal Declaration
    struct IllegalDecl : Decl
    {
      IllegalDecl( Lex::Token const &tok ) : Decl(tok, NULL, NULL) {}
      virtual ~IllegalDecl() {}

      void print( Printer const p ) const;
    }; // end struct IllegalDeclaration

    /// Type Specifier
    struct IllegalTypeSpecifier : TypeSpecifier
    {
      IllegalTypeSpecifier( Lex::Token const &tok, Decl * a, Decl * b ) :
        TypeSpecifier(tok,a,b) {}
      virtual ~IllegalTypeSpecifier() {}

      void print( Printer const p ) const;
    };

    // IllegalDeclarator
    struct IllegalDeclarator : Declarator 
    {
      IllegalDeclarator( Lex::Token const &tok ) :
        Declarator(tok) {}
      virtual ~IllegalDeclarator() {}
      
      void print( Printer const p ) const;
    };
    
    /// DeclList 
    struct DeclList : Locatable
    {
      DeclList( Lex::Token const &tok, std::vector<Decl const *> declVector ) :
        Locatable(tok), declVector(declVector) {}
      virtual ~DeclList() {}

      void print( Printer const p ) const;
      
      std::vector<Decl const *> declVector;
    };

    // IllegalDeclList
    struct IllegalDeclList : DeclList 
    {
      IllegalDeclList( Lex::Token const &tok, std::vector<Decl const *> declVector ) :
        DeclList(tok, declVector) {}
      virtual ~IllegalDeclList() {}
      
      void print( Printer const p ) const;
    };

   /// FunctionDef
    struct FunctionDef : ExternalDecl 
    {
      FunctionDef( Lex::Token const &tok, TypeSpecifier const * typeSpec,
         Declarator const * declarator, DeclList const * declList,
         CompoundStmt const * cStmt ) :
       ExternalDecl(tok), typeSpec(typeSpec), declarator(declarator),
     declList(declList), cStmt(cStmt) {}
      virtual ~FunctionDef() {}
      
      void print( Printer const p ) const;
      TypeSpecifier const * typeSpec;
      Declarator const * declarator;
      DeclList const * declList;
      CompoundStmt const * cStmt;
    };
    /// IllegalFunctionDef
    struct IllegalFunctionDef : FunctionDef 
    {
      IllegalFunctionDef( Lex::Token const &tok ) :
        FunctionDef(tok, NULL, NULL, NULL, NULL ) {}
      virtual ~IllegalFunctionDef() {}
      
      void print( Printer const p ) const;
    };
  } // end namespace AST
} // end namespace C4

#endif
