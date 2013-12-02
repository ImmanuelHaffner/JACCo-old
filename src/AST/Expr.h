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
#include "Locatable.h"
#include "Printable.h"
#include "Type.h"


namespace C4
{
  namespace AST
  {
    /// Expression
    struct Expr : Locatable, Printable
    {
      explicit Expr( Lex::Token const &tok ) : Locatable(tok) {}
      virtual ~Expr() {}

      // TODO implement in sub-classes
      virtual void print( Printer const ) const {}

      friend std::ostream & operator<<( std::ostream &out, Expr const &expr );
    }; // end struct Expression
    std::ostream & operator<<( std::ostream &out, Expr const &expr );

    struct IllegalExpr : Expr
    {
      explicit IllegalExpr( Lex::Token const &tok ) : Expr(tok) {}
      virtual ~IllegalExpr() {}

      friend std::ostream & operator<<( std::ostream &out,
          IllegalExpr const &expr );
    }; // end struct IllegalExpression
    std::ostream & operator<<( std::ostream &out, IllegalExpr const &expr );

    /// Expression list
    struct ExprList : Expr
    {
      explicit ExprList( Lex::Token const &tok ) : Expr(tok) {}
      virtual ~ExprList() {}

      friend std::ostream & operator<<( std::ostream &out,
          ExprList const &expr );
    }; // end struct ExprList
    std::ostream & operator<<( std::ostream &out, ExprList const &list );

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
      friend std::ostream & operator<<( std::ostream &out,
          Variable const &var );
    }; // end struct Variable
    std::ostream & operator<<( std::ostream &out, Variable const &var );

    /// Constant
    struct Constant : Expr
    {
      explicit Constant( Lex::Token const &tok ) : Expr(tok)
      {
        assert( tok.kind == Lex::TK::CONSTANT && "token must be a constant" );
      }

      ~Constant() {}

      friend std::ostream & operator<<( std::ostream &out,
          Constant const &con ); 
      void print( Printer const ) const;
    }; // end struct Constant
    std::ostream & operator<<( std::ostream &out, Constant const &con );

    /// String-Literal
    struct StringLiteral : Expr
    {
      explicit StringLiteral( Lex::Token const &tok ) : Expr(tok)
      {
        assert( tok.kind == Lex::TK::STRING_LITERAL
            && "token must be a string-literal" );
      }

      ~StringLiteral() {}

      friend std::ostream & operator<<( std::ostream &out,
          StringLiteral const &lit );
    }; // end struct StringLiteral
    std::ostream & operator<<( std::ostream &out, StringLiteral const &lit );

    /// Cast Expression
    struct CastExpr : Expr
    {
      CastExpr( Lex::Token const &tok, Expr const &expr ) :
        Expr(tok), expr(expr) {}
      virtual ~CastExpr() {}

      friend std::ostream & operator<<( std::ostream &out,
          CastExpr const &expr );

      // TODO type
      Expr const &expr;
    }; // end struct CastExpr
    std::ostream & operator<<( std::ostream &out, CastExpr const &expr );

    /// Binary Expression
    struct BinaryExpr : Expr
    {
      BinaryExpr( Lex::Token const &tok, Expr const * const lhs,
          Expr const * const rhs ) : Expr(tok), lhs(lhs), rhs(rhs) {}

      virtual ~BinaryExpr() {}
      void print( Printer const p ) const;
      friend std::ostream & operator<<( std::ostream &out,
          BinaryExpr const &expr );

      Expr const * const lhs;
      Expr const * const rhs;
    }; // end struct BinaryExpr
    std::ostream & operator<<( std::ostream &out, BinaryExpr const &expr );

    /// Conditional Expression
    struct ConditionalExpr : Expr
    {
      ConditionalExpr( Lex::Token const &tok, Expr const * const cond,
          Expr const * const lhs, Expr const * const rhs ) :
        Expr(tok), cond(cond), lhs(lhs), rhs(rhs) {}
      ~ConditionalExpr() {}

      friend std::ostream & operator<<( std::ostream &out,
          ConditionalExpr const &expr );

      Expr const * const cond;
      Expr const * const lhs;
      Expr const * const rhs;
      void print( Printer const ) const;

    }; // end struct ConditionalExpr
    std::ostream & operator<<( std::ostream &out, ConditionalExpr const &expr );

    /// Assignment Expression
    struct AssignmentExpr : BinaryExpr
    {
      AssignmentExpr( Lex::Token const & tok, Expr const * const lhs,
          Expr const * const rhs ) :
        BinaryExpr(tok, lhs, rhs) {}

      ~AssignmentExpr() {};
      virtual void print( Printer const ) const;
    }; // end struct AssignmentExpr
    std::ostream & operator<<( std::ostream &out, AssignmentExpr const &expr );

    /// Unary Expression
    struct UnaryExpr : Expr
    {
      UnaryExpr( Lex::Token const &tok ) : Expr(tok) {}
      virtual ~UnaryExpr() {}

      friend std::ostream & operator<<( std::ostream &out,
          UnaryExpr const &expr );
    }; // end struct UnaryExpr
    std::ostream & operator<<( std::ostream &out, UnaryExpr const &expr );

    /// Postfix Expression
    struct PostfixExpr : UnaryExpr
    {
      PostfixExpr( Lex::Token const &tok ) : UnaryExpr(tok) {}
      virtual ~PostfixExpr() {}

      friend std::ostream & operator<<( std::ostream &out,
          PostfixExpr const &expr );
    }; // end struct PostfixExpression
    std::ostream & operator<<( std::ostream &out, PostfixExpr const &expr );

    /// Subscript Expression
    struct SubscriptExpr : PostfixExpr
    {
      SubscriptExpr( Lex::Token const &tok, Expr const * const expr,
          Expr const *index ) :
        PostfixExpr(tok), expr(expr), index(index) {}
      ~SubscriptExpr() {}

      void print( Printer const p ) const;
      friend std::ostream & operator<<( std::ostream &out,
          SubscriptExpr const &expr );

      Expr const * const expr;
      Expr const * const index; 
    }; // end struct SubscriptExpr
    std::ostream & operator<<( std::ostream &out, SubscriptExpr const &expr );

    /// Dot Expression
    struct DotExpr : PostfixExpr
    {
      DotExpr( Lex::Token const &tok, Expr const &lhs, Lex::Token const &rhs ) :
        PostfixExpr(tok), lhs(lhs), rhs(rhs) {}
      ~DotExpr()
      {
        assert( rhs.kind == Lex::TK::IDENTIFIER &&
            "rhs of subscript must be an identifier" );
      }

      friend std::ostream & operator<<( std::ostream &out,
          DotExpr const &expr );

      Expr const &lhs;
      Lex::Token const &rhs;
      virtual void print( Printer const ) const;

    }; // end struct DotExpr
    std::ostream & operator<<( std::ostream &out, DotExpr const &expr );

    /// Arrow Expression
    struct ArrowExpr : DotExpr
    {
      ArrowExpr( Lex::Token const &tok, Expr const &lhs,
          Lex::Token const &rhs ) :
        DotExpr(tok, lhs, rhs) {}
      ~ArrowExpr() {}

      void print( Printer const ) const;
      friend std::ostream & operator<<( std::ostream &out,
          ArrowExpr const &expr );
    }; // end struct ArrowExpr
    std::ostream & operator<<( std::ostream &out, ArrowExpr const &expr );

    /// Function Call Expression
    struct FunctionCall : PostfixExpr
    {
      FunctionCall( Lex::Token const &tok, Expr const &expr
          /* TODO add argument-expr-list */ ) :
        PostfixExpr(tok), expr(expr) {}
      ~FunctionCall() {}

      void print( Printer const p ) const;
      friend std::ostream & operator<<( std::ostream &out,
          FunctionCall const &expr );

      Expr const &expr; 
    }; // end struct FunctionCall
    std::ostream & operator<<( std::ostream &out, FunctionCall const &expr );

    /// Post Increment Expression
    struct PostIncExpr : PostfixExpr
    {
      PostIncExpr( Lex::Token const &tok, Expr const &expr ) :
        PostfixExpr(tok), expr(expr) {}
      ~PostIncExpr() {}

      void print( Printer const ) const;
      friend std::ostream & operator<<( std::ostream &out,
          PostIncExpr const &expr );

      Expr const &expr;
    }; // end struct PostIncExpr
    std::ostream & operator<<( std::ostream &out, PostIncExpr const &expr );

    /// Post Decrement Expression
    struct PostDecExpr : PostfixExpr
    {
      PostDecExpr( Lex::Token const &tok, Expr const &expr ) :
        PostfixExpr(tok), expr(expr) {}
      ~PostDecExpr() {}

      void print( Printer const ) const;
      friend std::ostream & operator<<( std::ostream &out,
          PostDecExpr const &expr );

      Expr const &expr;
    }; // end struct PostDecExpr
    std::ostream & operator<<( std::ostream &out, PostDecExpr const &expr );

    /// Pre Increment Expression
    struct PreIncExpr : UnaryExpr
    {
      PreIncExpr( Lex::Token const &tok, Expr const * const expr ) :
        UnaryExpr(tok), expr(expr) {}
      ~PreIncExpr() {}

      void print( Printer const ) const;
      friend std::ostream & operator<<( std::ostream &out,
          PreIncExpr const &expr );

      Expr const * const expr; 
    }; // end struct PreIncExpr
    std::ostream & operator<<( std::ostream &out, PreIncExpr const &expr );

    /// Pre Decrement Expression
    struct PreDecExpr : UnaryExpr
    {
      PreDecExpr( Lex::Token const &tok, Expr const * const expr ) :
        UnaryExpr(tok), expr(expr) {}
      ~PreDecExpr() {}

      void print( Printer const ) const;
      friend std::ostream & operator<<( std::ostream &out,
          PreDecExpr const &expr );

      Expr const * const expr; 
    }; // end struct PreDecExpr
    std::ostream & operator<<( std::ostream &out, PreDecExpr const &expr );

    /// Sizeof Expression
    struct SizeofExpr : UnaryExpr
    {
      SizeofExpr( Lex::Token const &tok, Expr const * const expr ) :
        UnaryExpr(tok), expr(expr) {}
      ~SizeofExpr() {}

      void print( Printer const p ) const;
      friend std::ostream & operator<<( std::ostream &out,
          SizeofExpr const &expr );

      Expr const * const expr; 
    }; // end struct UnaryExpr
    std::ostream & operator<<( std::ostream &out, SizeofExpr const &expr );

    /// Sizeof Type Expression
    struct SizeofTypeExpr : UnaryExpr
    {
      SizeofTypeExpr( Lex::Token const &tok, Type const * const type ) :
        UnaryExpr(tok), type(type) {}
      ~SizeofTypeExpr() {}

      void print( Printer const p ) const;
      friend std::ostream & operator<<( std::ostream &out,
          SizeofTypeExpr const &expr );

      Type const * const type; 
    }; // end struct UnaryExpr
    std::ostream & operator<<( std::ostream &out, SizeofTypeExpr const &expr );
  } // end namespace AST
} // end namespace C4

#endif
