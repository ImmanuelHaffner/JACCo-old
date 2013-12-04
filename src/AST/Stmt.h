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
#include "Locatable.h"


namespace C4
{
  namespace AST
  {
    // Forward declaration
    struct Expr;

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

    /// If Statement
    struct IfStmt : Stmt
    {
      IfStmt( Lex::Token const tok, Expr const * const Cond,
          Stmt const * const Then ) :
      Stmt(tok), Cond(Cond), Then(Then), Else(NULL) {}

      IfStmt( Lex::Token const tok, Expr const * const Cond,
          Stmt const * const Then, Stmt const * const Else ) :
      Stmt(tok), Cond(Cond), Then(Then), Else(Else) {}

      ~IfStmt() {}

      Expr const * const Cond;
      Stmt const * const Then;
      Stmt const * const Else;
    }; // end struct IfStmt

    // Switch Statement
    struct SwitchStmt : Stmt
    {
      SwitchStmt( Lex::Token const &tok, Expr const * const Cond,
          Stmt const * const Body ) : Stmt(tok), Cond(Cond), Body(Body) {}
      ~SwitchStmt() {}

      Expr const * const Cond;
      Stmt const * const Body;
    }; // end struct SwitchStmt

    // While Statement
    struct WhileStmt : Stmt
    {
      WhileStmt( Lex::Token const &tok, Expr const * const Cond,
          Stmt const * const Body ) : Stmt(tok), Cond(Cond), Body(Body) {}
      ~WhileStmt() {}

      Expr const * const Cond;
      Stmt const * const Body;
    }; // end struct WhileStmt

    // Do-While Statement
    struct DoStmt : Stmt
    {
      DoStmt( Lex::Token const &tok, Stmt const * const Body,
          Expr const * const Cond ) : Stmt(tok), Body(Body), Cond(Cond) {}

      Stmt const * const Body;
      Expr const * const Cond;
    }; // end struct DoStmt
  } // end namespace AST
} // end namespace C4

#endif
