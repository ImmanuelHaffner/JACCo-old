///===--- Decl.h ----------------------------------------------------------===//
//
//  ~~~ The C4 Compiler ~~~
//
//  This file defines the Abstract Syntax tree interface.
//
//===----------------------------------------------------------------------===//


#ifndef C4_DECL_H
#define C4_DECL_H


#include <iostream>
#include <vector>
#include "Locatable.h"
#include "List.h"
#include "../util.h"
#include "../Support/EntityHolder.h"


/* Forward declarations */
namespace C4
{
  namespace Sema
  {
    struct Env;
  }

  namespace CodeGen
  {
    struct CodeGenFunction;
  }
}

namespace llvm
{
  class Value;
}


namespace C4
{
  namespace AST
  {
    /* Forward declarations */
    struct TypeSpecifier;
    struct CompoundStmt;



    /// External Declaration
    struct ExtDecl : Printable
    {
      virtual ~ExtDecl() {}

      virtual void emit( CodeGen::CodeGenFunction &CGF, bool isGlobal = false )
        const = 0;
    }; // end struct ExtDecl


    /// Illegal External Declaration
    struct IllegalExtDecl : Locatable, ExtDecl
    {
      IllegalExtDecl( Lex::Token const &tok ) : Locatable(tok) {}
      ~IllegalExtDecl() {}

      void print( Printer const p ) const;
      void emit( CodeGen::CodeGenFunction &, bool ) const;
    }; // end struct IllegalExtDecl


    /// Declaration
    struct Declarator;
    struct Decl : ExtDecl, Locatable, EntityHolder
    {
      Decl( Lex::Token const &tok, TypeSpecifier const * const typeSpec,
          Declarator const * const declarator = NULL )
        : Locatable(tok), typeSpec(nonNull(typeSpec)), declarator(declarator)
      {}

      virtual ~Decl() {}

			virtual void print( Printer const p ) const;

      /// \return always NULL
      virtual Sema::Type const * analyze( Sema::Env &env ) const;
      virtual void emit( CodeGen::CodeGenFunction &CGF, bool isGlobal = false )
        const;

      TypeSpecifier const * const typeSpec;
      Declarator const * const declarator;
    }; // end struct Declaration


    struct IllegalDecl : Decl
    {
      IllegalDecl( Lex::Token const &tok, TypeSpecifier const * const typeSpec )
        : Decl(tok, typeSpec) {}
      ~IllegalDecl() {}

      void print( Printer const p ) const;
      Sema::Type const * analyze( Sema::Env &env ) const;
      void emit( CodeGen::CodeGenFunction &, bool ) const;
    }; // end IllegalDecl


    /// Struct Declaration List
    struct StructDecl;
    struct StructDeclList : List< StructDecl >
    {
      StructDeclList() {}
      ~StructDeclList() {}

      StructDeclList( std::vector< StructDecl const * > &decls ) :
        List(decls) {}

			void print( Printer const p ) const;
      void analyze( Sema::Env &env ) const; 
		}; // end struct StructDeclList

    /// Struct Declaration
    struct StructDeclaratorList;
    struct StructDecl : Decl
    {
      StructDecl( Lex::Token const &tok, TypeSpecifier const * const typeSpec,
          StructDeclaratorList const * const structDeclarators )
        : Decl(tok, typeSpec), structDeclarators(structDeclarators)
      {}

      StructDeclaratorList const * const structDeclarators;

			void print( Printer const p ) const;
      Sema::Type const * analyze( Sema::Env &env ) const;
      void emit( CodeGen::CodeGenFunction &CGF, bool isGlobal = false ) const;
		}; // end struct StructDecl


    /// Parameter Declaration
    struct ParamDecl : Decl
    {
      ParamDecl( Lex::Token const &tok, TypeSpecifier const * const typeSpec,
          Declarator const * const declarator = NULL ) :
        Decl(tok, typeSpec, declarator)
      {}

      ~ParamDecl() {}

			void print( Printer const p ) const;
      Sema::Type const * analyze( Sema::Env &env ) const;
      void emit( CodeGen::CodeGenFunction &CGF, bool isGlobal = false ) const;
		}; // end struct ParamDecl

    /// Parameter List
    struct ParamList : List< ParamDecl >
    {
      ParamList() {}
      ParamList( std::vector< ParamDecl const * > &params ) : List(params) {}
			~ParamList() {}
			void print( Printer const p ) const;
      std::vector< Sema::Type const * >  analyze( Sema::Env &env ) const;
		}; // end struct ParamList

		/// Declarator
    struct Declarator : Locatable
    {
      Declarator( Lex::Token const &tok ) : Locatable(tok) {}
      virtual ~Declarator() {}

      virtual Entity * analyze( Sema::Env &env,
					Sema::Type const * const t )
        const = 0;
    }; // end struct Declarator

    /// Identifier
    struct Identifier : Declarator, EntityHolder
    {
      Identifier( Lex::Token const &tok ) : Declarator(tok) {}
      ~Identifier() {}

      void print( Printer const p ) const;
      Entity * analyze( Sema::Env &env, Sema::Type const * const t )
        const;
    }; // end struct Identifier


    /// PointerDeclarator
    struct PointerDeclarator : Declarator
    {
      PointerDeclarator( Lex::Token const &tok,
          Declarator const * const declarator )
        : Declarator(tok), declarator(declarator)
      {}

      ~PointerDeclarator() {}

			void print( Printer const p ) const;
      Entity * analyze( Sema::Env &env,
					Sema::Type const * const t ) const;

      Declarator const * const declarator;
    }; // end struct PointerDeclarator

    /// FunctionDeclarator
    struct FunctionDeclarator : Declarator
    {
      FunctionDeclarator( Lex::Token const &tok,
          Declarator const * const declarator,
          ParamList const * const params )
        : Declarator(tok), declarator(declarator),
        params(nonNull(params))
      {}

      ~FunctionDeclarator() {}

      void print( Printer const p ) const;
      Entity * analyze( Sema::Env &env,
					Sema::Type const * const t ) const;

      Declarator const * const declarator;
      ParamList const * const params;
    }; // end struct FunctionDeclarator


    /// Illegal Declarator
    struct IllegalDeclarator : Declarator
    {
      IllegalDeclarator( Lex::Token const &tok ) : Declarator(tok) {}
      ~IllegalDeclarator() {}

			void print( Printer const p ) const;
      Entity * analyze( Sema::Env &env, Sema::Type const * t ) const;
		}; // end struct IllegalDeclarator

    /// Struct Declarator List
    struct StructDeclaratorList : List< Declarator >
    {
      StructDeclaratorList() {}

      StructDeclaratorList( std::vector< Declarator const * > &declarators ) :
        List(declarators) {}

      ~StructDeclaratorList() {}

			void print( Printer const p ) const;
      void analyze( Sema::Env &env, Sema::Type const * t ) const;
		}; // end struct StructDeclaratorList


    /// Declaration List
    struct DeclList : List< Decl >
    {
      DeclList() {}

      DeclList( std::vector< Decl const * > &decls ) : List(decls) {}

      ~DeclList() {}

      void print( Printer const p ) const;
    }; // end struct DeclList


    /// Function Definition
    struct FunctionDef : ExtDecl
    {
      FunctionDef( Decl const * const decl,
          CompoundStmt const * const compStmt ) : decl(nonNull(decl)),
      compStmt(nonNull(compStmt))
      {}

      ~FunctionDef() {}

			void print( Printer const p ) const;
      void analyze( Sema::Env &env ) const;
      void emit( CodeGen::CodeGenFunction &CGF, bool isGlobal = false ) const;

      Decl const * const decl;
      CompoundStmt const * const compStmt;
    }; // end struct FunctionDef
  } // end namespace AST
} // end namespace C4

#endif
