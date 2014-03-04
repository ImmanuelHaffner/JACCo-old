//===--- ASTFactory.h -----------------------------------------------------===//
//
//  ~~~ The C4 Compiler ~~~
//
//  This file defines the AST factory used by the parser.
//
//===----------------------------------------------------------------------===//


#ifndef C4_AST_FACTORY
#define C4_AST_FACTORY


#include "AST.h"
#include "../Sema/Env.h"


namespace C4
{
  namespace AST
  {
    struct ASTFactory
    {
      ASTFactory(
#ifndef NOSEMA
          Sema::Env &env
#endif
          )
#ifndef NOSEMA
        : env(env)
#endif
        {}
      ~ASTFactory() {}


#define TOK Lex::Token const &tok

      inline TranslationUnit const * getTranslationUnit(
          std::vector< ExtDecl const * > extDecls )
      {
        return new TranslationUnit( extDecls );
      }

      //===----------------------------------------------------------------===//
      //
      //  Expressions
      //
      //===----------------------------------------------------------------===//

      inline IllegalExpr const * getIllegalExpr( TOK )
      {
        return new IllegalExpr( tok );
      }

      inline ExprList const * getExprList( TOK,
          std::vector< Expr const * > &list )
      {
        return new ExprList( tok, list );
      }

      inline Variable const * getVariable( TOK )
      {
        Variable * variable = new Variable( tok );
#ifndef NOSEMA
        variable->analyze(env);
#endif
        return variable;
      }

      inline Constant const * getConstant( TOK )
      {
        Constant *constant = new Constant( tok );
#ifndef NOSEMA
        constant->analyze();
#endif
        return constant;
      }

      inline StringLiteral const * getStringLiteral( TOK )
      {
        StringLiteral *string = new StringLiteral( tok );
#ifndef NOSEMA
        string->analyze();
#endif
        return string;
      }

      inline BinaryExpr const * getBinaryExpr( TOK, Expr const * const lhs,
          Expr const * const rhs )
      {
        return new BinaryExpr( tok, lhs, rhs );
      }

      inline ConditionalExpr const * getConditionalExpr( TOK,
          Expr const * const cond, Expr const * const lhs,
          Expr const * const rhs )
      {
        return new ConditionalExpr( tok, cond, lhs, rhs );
      }

      inline AssignmentExpr const * getAssignmentExpr( TOK,
          Expr const * const lhs, Expr const * const rhs )
      {
        return new AssignmentExpr( tok, lhs, rhs );
      }

      inline UnaryOperation const * getUnaryOperation( TOK,
          Expr const * const expr )
      {
        return new UnaryOperation( tok, expr );
      }

      inline SubscriptExpr const * getSubscriptExpr( TOK,
          Expr const * const expr, Expr const * const index )
      {
        return new SubscriptExpr( tok, expr, index );
      }

      inline DotExpr const * getDotExpr( TOK, Expr const * const expr,
          Lex::Token const &id )
      {
        return new DotExpr( tok, expr, id );
      }

      inline ArrowExpr const * getArrowExpr( TOK, Expr const * const expr,
          Lex::Token const &id )
      {
        return new ArrowExpr( tok, expr, id );
      }

      inline FunctionCall const * getFunctionCall( TOK, Expr const * const fun,
          Expr const * const args = NULL )
      {
        return new FunctionCall( tok, fun, args );
      }

      inline PostIncExpr const * getPostIncExpr( TOK, Expr const * const expr )
      {
        return new PostIncExpr( tok, expr );
      }

      inline PostDecExpr const * getPostDecExpr( TOK, Expr const * const expr )
      {
        return new PostDecExpr( tok, expr );
      }

      inline PreIncExpr const * getPreIncExpr( TOK, Expr const * const expr )
      {
        return new PreIncExpr( tok, expr );
      }

      inline PreDecExpr const * getPreDecExpr( TOK, Expr const * const expr )
      {
        return new PreDecExpr( tok, expr );
      }

      inline SizeofExpr const * getSizeofExpr( TOK, Expr const * const expr )
      {
        return new SizeofExpr( tok, expr );
      }

      inline SizeofTypeExpr const * getSizeofTypeExpr( TOK,
          TypeName const * const typeName )
      {
        return new SizeofTypeExpr( tok, typeName );
      }


      //===----------------------------------------------------------------===//
      //
      //  Declarations
      //
      //===----------------------------------------------------------------===//

      inline IllegalExtDecl const * getIllegalExtDecl( TOK )
      {
        return new IllegalExtDecl( tok );
      }

      inline Decl * getDecl( TOK, TypeSpecifier const * const typeSpec,
          Declarator const * const declarator = NULL )
      {
        Decl * const decl = new Decl( tok, typeSpec, declarator );
#ifndef NOSEMA
        decl->analyze_nc( env );
#endif
        return decl;
      }

      inline IllegalDecl const * getIllegalDecl( TOK,
          TypeSpecifier const * const typeSpec )
      {
        return new IllegalDecl( tok, typeSpec );
      }

      inline StructDeclList const * getStructDeclList(
          std::vector< StructDecl const * > &decls )
      {
        return new StructDeclList( decls );
      }

      inline StructDecl const * getStructDecl(
          Lex::Token const &tok, TypeSpecifier const * const typeSpec,
          StructDeclaratorList const * const structDeclarators )
      {
        return new StructDecl( tok, typeSpec, structDeclarators );
      }

      inline ParamDecl const * getParamDecl(
          Lex::Token const &tok, TypeSpecifier const * const typeSpec,
          Declarator const * const declarator = NULL )
      {
        ParamDecl const * const decl = new ParamDecl( tok, typeSpec,
            declarator );
        return decl;
      }

      inline ParamList const * getParamList(
          std::vector< ParamDecl const * > &params )
      {
        return new ParamList( params );
      }

      inline ParamList const * getParamList()
      {
        return new ParamList();
      }

      inline Identifier const * getIdentifier( TOK )
      {
        return new Identifier( tok );
      }

      inline PointerDeclarator const * getPointerDeclarator( TOK,
          Declarator const * const declarator )
      {
        return new PointerDeclarator( tok, declarator );
      }

      inline FunctionDeclarator const * getFunctionDeclarator( TOK,
          Declarator const * const declarator, ParamList const * const params )
      {
        return new FunctionDeclarator( tok, declarator, params );
      }

      inline IllegalDeclarator const * getIllegalDeclarator( TOK )
      {
        return new IllegalDeclarator( tok );
      }

      inline StructDeclaratorList const * getStructDeclaratorList(
          std::vector< Declarator const * > &declarators )
      {
        return new StructDeclaratorList( declarators );
      }

      inline DeclList const * getDeclList( std::vector< Decl const * > &decls )
      {
        return new DeclList( decls );
      }

      inline FunctionDef const * getFunctionDef(
          Decl const * const decl,
          CompoundStmt const * const compStmt )
      {
        FunctionDef const * const funDef = new FunctionDef( decl, compStmt );
#ifndef NOSEMA
        funDef->analyze( env );
#endif
        return funDef;
      }


      //===----------------------------------------------------------------===//
      //
      //  Statements
      //
      //===----------------------------------------------------------------===//

      inline IllegalStmt const * getIllegalStmt( TOK )
      {
        return new IllegalStmt( tok );
      }

      inline ExprStmt const * getExprStmt( TOK, Expr const * const expr = NULL )
      {
        return new ExprStmt( tok, expr );
      }

      inline CaseStmt const * getCaseStmt( TOK, Expr const * const expr,
          Stmt const * const stmt )
      {
        return new CaseStmt( tok, expr, stmt );
      }

      inline LabelStmt const * getLabelStmt( TOK, Stmt const * const stmt )
      {
        LabelStmt const * labelStmt = new LabelStmt( tok, stmt );
#ifndef NOSEMA
        labelStmt->analyze( env );
#endif
        return labelStmt; 
      }

      inline IfStmt const * getIfStmt( TOK, Expr const * const Cond,
          Stmt const * const Then, Stmt const * const Else = NULL )
      {
        return new IfStmt( tok, Cond, Then, Else );
      }

      inline SwitchStmt const * getSwitchStmt( TOK, Expr const * const Cond,
          Stmt const * const Body )
      {
        return new SwitchStmt( tok, Cond, Body );
      }

      inline WhileStmt const * getWhileStmt( TOK, Expr const * const Cond,
          Stmt const * const Body )
      {
        return new WhileStmt( tok, Cond, Body );
      }

      inline DoStmt const * getDoStmt( TOK, Stmt const * const Body,
          Expr const * const Cond )
      {
        return new DoStmt( tok, Body, Cond );
      }

      inline ForStmt const * getForStmt( TOK, Expr const * const Init,
          Expr const * const Cond, Expr const * const Step,
          Stmt const * const Body )
      {
        return new ForStmt( tok, Init, Cond, Step, Body );
      }

      inline ForStmt const * getForStmt( TOK, Decl const * const InitDecl,
          Expr const * const Cond, Expr const * const Step,
          Stmt const * const Body )
      {
        return new ForStmt( tok, InitDecl, Cond, Step, Body );
      }

      inline BreakStmt const * getBreakStmt( TOK )
      {
        BreakStmt const * const stmt = new BreakStmt( tok );
#ifndef NOSEMA
        stmt->analyze();
#endif
        return stmt;
      }

      inline ContinueStmt const * getContinueStmt( TOK )
      {
        ContinueStmt const * const stmt = new ContinueStmt( tok );
#ifndef NOSEMA
        stmt->analyze();
#endif
        return stmt;
      }

      inline GotoStmt const * getGotoStmt( TOK )
      {
        GotoStmt const * stmt = new GotoStmt( tok );
#ifndef NOSEMA
        stmt->analyze( env );
#endif
        return stmt; 
      }

      inline ReturnStmt const * getReturnStmt( TOK,
          Expr const * const expr = NULL )
      {
        return new ReturnStmt( tok, expr );
      }

      inline BlockItem const * getBlockItem( Stmt const * const stmt )
      {
        return new BlockItem( stmt );
      }

      inline BlockItem const * getBlockItem( Decl const * const decl )
      {
        return new BlockItem( decl );
      }

      inline CompoundStmt const * getCompoundStmt( TOK,
          std::vector< BlockItem const * > &items )
      {
        return new CompoundStmt( tok, items );
      }

      //===----------------------------------------------------------------===//
      //
      //  Types
      //
      //===----------------------------------------------------------------===//

      inline TypeSpecifier const * getTypeSpecifier( TOK )
      {
        return new TypeSpecifier( tok );
      }

      inline TypeName const * getTypeName( TOK,
          TypeSpecifier const * const typeSpec,
          Declarator const * const declarator = NULL )
      {
        return new TypeName( tok, typeSpec, declarator );
      }

      inline IllegalTypeSpecifier const * getIllegalTypeSpecifier( TOK )
      {
        return new IllegalTypeSpecifier( tok );
      }

      inline StructSpecifier const * getStructSpecifier( TOK,
          Lex::Token const * const name,
          StructDeclList const * const decls = NULL )
      {
        return new StructSpecifier( tok, name, decls );
      }

      inline StructSpecifier const * getStructSpecifier( TOK,
          StructDeclList const * const decls )
      {
        return new StructSpecifier( tok, decls );
      }

#undef TOK

#ifndef NOSEMA
      private:
      Sema::Env &env;
#endif
    };
  } // end namespace AST
} // end namespace C4


#endif
