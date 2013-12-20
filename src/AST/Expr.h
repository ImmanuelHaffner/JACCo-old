//===--- Expr.h -----------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_EXPR_H
#define C4_EXPR_H

#include <iostream>
#include "List.h"
#include "Locatable.h"
#include "../Sema/Sema.h"


namespace C4
{
	namespace AST
	{
		// Forward declaration
		struct TypeName;



		/// Expression
		struct Expr : Locatable, Sema::SemaObject
		{
			explicit Expr( Lex::Token const &tok ) : Locatable(tok) {}
			virtual ~Expr() {}
		}; // end struct Expression


		/// Illegal Expression
		struct IllegalExpr : Expr
		{
			explicit IllegalExpr( Lex::Token const &tok ) : Expr(tok) {}
			virtual ~IllegalExpr() {}

			void print( Printer const p ) const;
		}; // end struct IllegalExpression


		/// Expression List
		struct ExprList : Expr, List< Expr >, Sema::SemaObject
		{
			explicit ExprList( Lex::Token const &tok ) : Expr(tok) {}
			~ExprList() {}

			void print( Printer const p ) const;
		}; // end struct ExprList


		/// Variable
		struct Variable : Expr
		{
			explicit Variable( Lex::Token const &tok ) : Expr(tok)
			{
				assert( tok.kind == Lex::TK::IDENTIFIER
						&& "token must be an identifier" );
			}
			~Variable() {}

			void print( Printer const p ) const;
		}; // end struct Variable


		/// Constant
		struct Constant : Expr
		{
			explicit Constant( Lex::Token const &tok ) : Expr(tok)
			{
				assert( tok.kind == Lex::TK::CONSTANT && "token must be a constant" );
			}
			~Constant() {}

			void print( Printer const p ) const;
		}; // end struct Constant


		/// String-Literal
		struct StringLiteral : Expr
		{
			explicit StringLiteral( Lex::Token const &tok ) : Expr(tok)
			{
				assert( tok.kind == Lex::TK::STRING_LITERAL
						&& "token must be a string-literal" );
			}
			~StringLiteral() {}

			void print( Printer const p ) const;
		}; // end struct StringLiteral


		/// Binary Expression
		struct BinaryExpr : Expr
		{
			BinaryExpr( Lex::Token const &tok, Expr const * const lhs,
					Expr const * const rhs ) : Expr(tok), lhs(lhs), rhs(rhs) {}
			virtual ~BinaryExpr() {}

			void print( Printer const p ) const;

			Expr const * const lhs;
			Expr const * const rhs;
		}; // end struct BinaryExpr


		/// Conditional Expression
		struct ConditionalExpr : Expr
		{
			ConditionalExpr( Lex::Token const &tok, Expr const * const cond,
					Expr const * const lhs, Expr const * const rhs ) :
				Expr(tok), cond(cond), lhs(lhs), rhs(rhs) {}
			~ConditionalExpr() {}

			void print( Printer const ) const;

			Expr const * const cond;
			Expr const * const lhs;
			Expr const * const rhs;
		}; // end struct ConditionalExpr


		/// Assignment Expression
		struct AssignmentExpr : BinaryExpr
		{
			AssignmentExpr( Lex::Token const & tok, Expr const * const lhs,
					Expr const * const rhs ) :
				BinaryExpr(tok, lhs, rhs) {}
			~AssignmentExpr() {};

			virtual void print( Printer const ) const;
		}; // end struct AssignmentExpr


		/// Unary Expression
		struct UnaryExpr : Expr
		{
			UnaryExpr( Lex::Token const &tok ) : Expr(tok) {}
			virtual ~UnaryExpr() {}

		}; // end struct UnaryExpr


		/// Unary Operation
		struct UnaryOperation : Expr
		{
			UnaryOperation( Lex::Token const &tok, Expr const * const expr )
				: Expr(tok), expr(expr) {}
			~UnaryOperation() {}

			void print( Printer const p ) const;

			Expr const * const expr;
		}; // end struct UnaryOperation


		/// Postfix Expression
		struct PostfixExpr : UnaryExpr
		{
			PostfixExpr( Lex::Token const &tok ) : UnaryExpr(tok) {}
			virtual ~PostfixExpr() {}
		}; // end struct PostfixExpression


		/// Subscript Expression
		struct SubscriptExpr : PostfixExpr
		{
			SubscriptExpr( Lex::Token const &tok, Expr const * const expr,
					Expr const * const index ) :
				PostfixExpr(tok), expr(expr), index(index) {}
			~SubscriptExpr() {}

			void print( Printer const p ) const;

			Expr const * const expr;
			Expr const * const index;
		}; // end struct SubscriptExpr


		/// Dot Expression
		struct DotExpr : PostfixExpr
		{
			DotExpr( Lex::Token const &tok, Expr const * const expr,
					Lex::Token const &id ) :
				PostfixExpr(tok), expr(expr), id(id)
			{
				assert( id.kind == Lex::TK::IDENTIFIER &&
						"rhs of dot- or arrow-expr must be an identifier" );
			}
			~DotExpr() {}

			virtual void print( Printer const p ) const;

			Expr const * const expr;
			Lex::Token const id;
		}; // end struct DotExpr


		/// Arrow Expression
		struct ArrowExpr : DotExpr
		{
			ArrowExpr( Lex::Token const &tok, Expr const * const expr,
					Lex::Token const &id ) :
				DotExpr(tok, expr, id) {}
			~ArrowExpr() {}

			void print( Printer const p ) const;
		}; // end struct ArrowExpr


		/// Function Call Expression
		struct FunctionCall : PostfixExpr
		{
			FunctionCall( Lex::Token const &tok, Expr const * const fun,
					Expr const * const args = NULL )
				: PostfixExpr(tok), fun(nonNull(fun)), args(args) {}
			~FunctionCall() {}

			void print( Printer const p ) const;

			Expr const * const fun;
			Expr const * const args;
		}; // end struct FunctionCall


		/// Post Increment Expression
		struct PostIncExpr : PostfixExpr
		{
			PostIncExpr( Lex::Token const &tok, Expr const &expr ) :
				PostfixExpr(tok), expr(expr) {}
			~PostIncExpr() {}

			void print( Printer const ) const;

			Expr const &expr;
		}; // end struct PostIncExpr


		/// Post Decrement Expression
		struct PostDecExpr : PostfixExpr
		{
			PostDecExpr( Lex::Token const &tok, Expr const &expr ) :
				PostfixExpr(tok), expr(expr) {}
			~PostDecExpr() {}

			void print( Printer const ) const;

			Expr const &expr;
		}; // end struct PostDecExpr


		/// Pre Increment Expression
		struct PreIncExpr : UnaryExpr
		{
			PreIncExpr( Lex::Token const &tok, Expr const * const expr ) :
				UnaryExpr(tok), expr(expr) {}
			~PreIncExpr() {}

			void print( Printer const ) const;

			Expr const * const expr;
		}; // end struct PreIncExpr


		/// Pre Decrement Expression
		struct PreDecExpr : UnaryExpr
		{
			PreDecExpr( Lex::Token const &tok, Expr const * const expr ) :
				UnaryExpr(tok), expr(expr) {}
			~PreDecExpr() {}

			void print( Printer const ) const;

			Expr const * const expr;
		}; // end struct PreDecExpr


		/// Sizeof Expression
		struct SizeofExpr : UnaryExpr
		{
			SizeofExpr( Lex::Token const &tok, Expr const * const expr ) :
				UnaryExpr(tok), expr(expr) {}
			~SizeofExpr() {}

			void print( Printer const p ) const;

			Expr const * const expr;
		}; // end struct UnaryExpr


		/// Sizeof Type Expression
		struct SizeofTypeExpr : UnaryExpr
		{
			SizeofTypeExpr( Lex::Token const &tok, TypeName const * const typeName )
				: UnaryExpr(tok), typeName(nonNull(typeName)) {}
			~SizeofTypeExpr() {}

			void print( Printer const p ) const;

			TypeName const * const typeName;
		}; // end struct UnaryExpr
	} // end namespace AST
} // end namespace C4

#endif
