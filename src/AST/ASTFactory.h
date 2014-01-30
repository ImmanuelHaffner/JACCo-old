//===--- ASTFactory.h -----------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the AST factory used by the parser.
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
			ASTFactory( Sema::Env &env ) : env(env) {}
			~ASTFactory() {}


#define TOK Lex::Token const &tok

      //===----------------------------------------------------------------===//
      //
      //  Expressions
      //
      //===----------------------------------------------------------------===//

			inline IllegalExpr const * getIllegalExpr( TOK )
			{
				return new IllegalExpr( tok );
			}

			ExprList const * getExprList( TOK, std::vector< Expr const * > &list )
			{
				return new ExprList( tok, list );
			}

			Variable const * getVariable( TOK )
			{
				return new Variable( tok );
			}

			Constant const * getConstant( TOK )
			{
				return new Constant( tok );
			}

			StringLiteral const * getStringLiteral( TOK )
			{
				return new StringLiteral( tok );
			}

			BinaryExpr const * getBinaryExpr( TOK, Expr const * const lhs,
					Expr const * const rhs )
			{
				return new BinaryExpr( tok, lhs, rhs );
			}

			ConditionalExpr const * getConditionalExpr( TOK, Expr const * const cond,
					Expr const * const lhs, Expr const * const rhs )
			{
				return new ConditionalExpr( tok, cond, lhs, rhs );
			}

			AssignmentExpr const * getAssignmentExpr( TOK,
					Expr const * const lhs, Expr const * const rhs )
			{
				return new AssignmentExpr( tok, lhs, rhs );
			}

			UnaryOperation const * getUnaryOperation( TOK, Expr const * const expr )
			{
				return new UnaryOperation( tok, expr );
			}

			SubscriptExpr const * getSubscriptExpr( TOK, Expr const * const expr,
					Expr const * const index )
			{
				return new SubscriptExpr( tok, expr, index );
			}

			DotExpr const * getDotExpr( TOK, Expr const * const expr,
					Lex::Token const &id )
			{
				return new DotExpr( tok, expr, id );
			}

			ArrowExpr const * getArrowExpr( TOK, Expr const * const expr,
					Lex::Token const &id )
			{
				return new ArrowExpr( tok, expr, id );
			}

			FunctionCall const * getFunctionCall( TOK, Expr const * const fun,
					Expr const * const args = NULL )
			{
				return new FunctionCall( tok, fun, args );
			}

			PostIncExpr const * getPostIncExpr( TOK, Expr const * const expr )
			{
				return new PostIncExpr( tok, expr );
			}

			PostDecExpr const * getPostDecExpr( TOK, Expr const * const expr )
			{
				return new PostDecExpr( tok, expr );
			}

			PreIncExpr const * getPreIncExpr( TOK, Expr const * const expr )
			{
				return new PreIncExpr( tok, expr );
			}

			PreDecExpr const * getPreDecExpr( TOK, Expr const * const expr )
			{
				return new PreDecExpr( tok, expr );
			}

			SizeofExpr const * getSizeofExpr( TOK, Expr const * const expr )
			{
				return new SizeofExpr( tok, expr );
			}

			SizeofTypeExpr const * getSizeofTypeExpr( TOK,
					TypeName const * const typeName )
			{
				return new SizeofTypeExpr( tok, typeName );
			}


      //===----------------------------------------------------------------===//
      //
      //  Declarations
      //
      //===----------------------------------------------------------------===//

			IllegalExtDecl const * getIllegalExtDecl( TOK )
			{
				return new IllegalExtDecl( tok );
			}

			Decl const * getDecl( TypeSpecifier const * const typeSpec,
					Declarator const * const declarator = NULL )
			{
				return new Decl( typeSpec, declarator );
			}

			IllegalDecl const * getIllegalDecl( TOK,
					TypeSpecifier const * const typeSpec )
			{
				return new IllegalDecl( tok, typeSpec );
			}

			StructDeclList const * getStructDeclList(
					std::vector< StructDecl const * > &decls )
			{
				return new StructDeclList( decls );
			}

			StructDecl const * getStructDecl( TypeSpecifier const * const typeSpec,
					StructDeclaratorList const * const structDeclarators )
			{
				return new StructDecl( typeSpec, structDeclarators );
			}

			ParamDecl const * getParamDecl( TypeSpecifier const * const typeSpec,
					Declarator const * const declarator = NULL )
			{
				return new ParamDecl( typeSpec, declarator );
			}

			ParamList const * getParamList( std::vector< ParamDecl const * > &params )
			{
				return new ParamList( params );
			}

			Identifier const * getIdentifier( TOK )
			{
				return new Identifier( tok );
			}

			PointerDeclarator const * getPointerDeclarator( TOK,
					Declarator const * const declarator )
			{
				return new PointerDeclarator( tok, declarator );
			}

			FunctionDeclarator const * getFunctionDeclarator( TOK,
					Declarator const * const declarator, ParamList const * const params )
			{
				return new FunctionDeclarator( tok, declarator, params );
			}

			IllegalDeclarator const * getIllegalDeclarator( TOK )
			{
				return new IllegalDeclarator( tok );
			}

			DirectDeclarator const * getDirectDeclarator( TOK )
			{
				return new DirectDeclarator( tok );
			}

			DirectDeclarator const * getDirectDeclarator( TOK,
					Declarator const * const declarator, ParamList const * const params )
			{
				return new DirectDeclarator( tok, declarator, params );
			}

			DirectDeclarator const * getDirectDeclarator( TOK,
					DirectDeclarator const * const directDeclarator,
					ParamList const * const params )
			{
				return new DirectDeclarator( tok, directDeclarator, params );
			}

			StructDeclaratorList const * getStructDeclaratorList(
					std::vector< Declarator const * > &declarators )
			{
				return new StructDeclaratorList( declarators );
			}

			DeclList const * getDeclList( std::vector< Decl const * > &decls )
			{
				return new DeclList( decls );
			}

			FunctionDef const * getFunctionDef( TypeSpecifier const * const typeSpec,
					Declarator const * const declarator,
					CompoundStmt const * const compStmt )
			{
				return new FunctionDef( typeSpec, declarator, compStmt );
			}

#undef TOK


			private:
			Sema::Env &env;
		};
	} // end namespace AST
} // end namespace C4


#endif
