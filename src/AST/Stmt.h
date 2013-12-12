//===--- Stmt.h ------------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the Abstract Syntax tree interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_STMT_H
#define C4_STMT_H

#include <iostream>
#include <vector>
#include "../util.h"
#include "List.h"
#include "Locatable.h"


namespace C4
{
  namespace AST
  {
    // Forward declaration
    struct Expr;
    struct Decl;
    struct DeclList;



    /// Statement
    struct Stmt : Locatable
    {
      Stmt( Lex::Token const &tok ) : Locatable(tok) {}
      virtual ~Stmt() {}
    }; // end struct Stmt


    /// Illegal Statement
    struct IllegalStmt : Stmt
    {
      IllegalStmt( Lex::Token const &tok ) : Stmt(tok) {}
      virtual ~IllegalStmt() {}

      void print ( Printer const p ) const;
    }; // end struct IllegalStmt


    /// Expression Statement
    struct ExprStmt : Stmt
    {
      ExprStmt( Lex::Token const &tok, Expr const * const expr = NULL )
        : Stmt(tok), expr(expr)
      {}

      ~ExprStmt() {}

      void print( Printer const p ) const;

      Expr const * const expr;
    }; // end struct ExprStmt


    /// Case Statement
    struct CaseStmt : Stmt
    {
      CaseStmt( Lex::Token const &tok, Expr const * const expr,
          Stmt const * const stmt )
        : Stmt(tok), expr(expr), stmt(stmt)
      {}

      void print( Printer const p ) const;

      Expr const * const expr;
      Stmt const * const stmt;
    }; // end struct CaseStmt


    /// Label Statement
    struct LabelStmt : Stmt
    {
      LabelStmt( Lex::Token const &tok, Stmt const * const stmt )
        : Stmt(tok), stmt(stmt)
      {
        assert( ( tok.kind == Lex::TK::Default ||
              tok.kind == Lex ::TK::IDENTIFIER ) &&
            "label name must be 'default' or identifier" );
      }
      ~LabelStmt() {}

      void print( Printer const p ) const;

      Stmt const * const stmt;
    }; // end struct CaseStmt


    /// If Statement
    struct IfStmt : Stmt
    {
      IfStmt( Lex::Token const &tok, Expr const * const Cond,
          Stmt const * const Then, Stmt const * const Else = NULL )
        : Stmt(tok), Cond(nonNull(Cond)), Then(nonNull(Then)), Else(Else)
      {}

      ~IfStmt() {}

      void print( Printer const p ) const;

      Expr const * const Cond;
      Stmt const * const Then;
      Stmt const * const Else;
    }; // end struct IfStmt


    /// Switch Statement
    struct SwitchStmt : Stmt
    {
      SwitchStmt( Lex::Token const &tok, Expr const * const Cond,
          Stmt const * const Body )
        : Stmt(tok), Cond(nonNull(Cond)), Body(nonNull(Body))
      {}

      ~SwitchStmt() {}

      void print( Printer const p ) const;

      Expr const * const Cond;
      Stmt const * const Body;
    }; // end struct SwitchStmt


    /// While Statement
    struct WhileStmt : Stmt
    {
      WhileStmt( Lex::Token const &tok, Expr const * const Cond,
          Stmt const * const Body )
        : Stmt(tok), Cond(nonNull(Cond)), Body(nonNull(Body))
      {}

      ~WhileStmt() {}

      void print( Printer const p ) const;

      Expr const * const Cond;
      Stmt const * const Body;
    }; // end struct WhileStmt


    /// Do-While Statement
    struct DoStmt : Stmt
    {
      DoStmt( Lex::Token const &tok, Stmt const * const Body,
          Expr const * const Cond )
        : Stmt(tok), Body(nonNull(Body)), Cond(nonNull(Cond))
      {}

      ~DoStmt() {}

      Stmt const * const Body;
      Expr const * const Cond;
    }; // end struct DoStmt


    /// For Statement
    struct ForStmt : Stmt
    {
      ForStmt( Lex::Token const &tok, ExprStmt const * const Init,
          ExprStmt const * const Cond, Expr const * const Step,
          Stmt const * const Body )
        : Stmt(tok), Init(nonNull(Init)), InitDecl(NULL), Cond(nonNull(Cond)),
        Step(Step), Body(nonNull(Body))
      {}

      ForStmt( Lex::Token const &tok, ExprStmt const * const Init,
          ExprStmt const * const Cond, Stmt const * const Body )
        : ForStmt(tok, Init, Cond, NULL, Body)
      {}

      ForStmt( Lex::Token const &tok, Decl const * const InitDecl,
          ExprStmt const * const Cond, Expr const * const Step,
          Stmt const * const Body )
        : Stmt(tok), Init(NULL), InitDecl(nonNull(InitDecl)),
        Cond(nonNull(Cond)), Step(Step), Body(nonNull(Body))
      {}

      ~ForStmt() {}

      void print( Printer const p ) const;

      ExprStmt const * const Init;
      Decl const * const InitDecl;
      ExprStmt const * const Cond;
      Expr const * const Step;
      Stmt const * const Body;
    }; // end struct ForStmt


    /// Break Statement
    struct BreakStmt : Stmt
    {
      BreakStmt( Lex::Token const &tok ) : Stmt(tok) {}
      ~BreakStmt() {}
    }; // end struct BreakStmt


    /// Continue Statement
    struct ContinueStmt : Stmt
    {
      ContinueStmt( Lex::Token const &tok ) : Stmt(tok) {}
      ~ContinueStmt() {}
    }; // end struct ContinueStmt


    /// Goto Statement
    struct GotoStmt : Stmt
    {
      GotoStmt( Lex::Token const &tok ) : Stmt(tok)
      {
        assert( tok.kind == Lex::TK::IDENTIFIER &&
            "must be the label of the jump target" );
      }

      ~GotoStmt() {}
    }; // end struct GotoStmt


    /// Return Statement
    struct ReturnStmt : Stmt
    {
      ReturnStmt( Lex::Token const &tok, Expr const * const expr = NULL )
        : Stmt(tok), expr(expr)
      {}

      ~ReturnStmt() {}

      void print( Printer const p ) const;

      Expr const * const expr;
    }; // end struct ReturnStmt


    /// Block Item
    struct BlockItem
    {
      BlockItem( Stmt const * const stmt ) : stmt(nonNull(stmt)), decl(NULL) {}
      BlockItem( Decl const * const decl ) : stmt(NULL), decl(nonNull(decl)) {}
      ~BlockItem() {}

      Stmt const * const stmt;
      Decl const * const decl;
    }; // end struct BlockItem


    /// Compound Statement
    struct CompoundStmt : Stmt, List< BlockItem >
    {
      CompoundStmt( Lex::Token const &tok ) : Stmt(tok) {}
      ~CompoundStmt() {}

      void print( Printer const p ) const;
    }; // end struct CompoundStmt
  } // end namespace AST
} // end namespace C4

#endif
