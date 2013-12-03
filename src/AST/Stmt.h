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
#include "Printable.h"


namespace C4
{
  namespace AST
  {
    // Forward declaration
    struct Expr;

    /// Statement
    struct Stmt : Locatable, Printable
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
      SwitchStmt( Lex::Token const &tok, Expr const * const expr,
          Stmt const * const stmt ) : Stmt(tok), expr(expr), stmt(stmt) {}
      ~SwitchStmt() {}

      Expr const * const expr;
      Stmt const * const stmt;
    };
  } // end namespace AST
} // end namespace C4

#endif
