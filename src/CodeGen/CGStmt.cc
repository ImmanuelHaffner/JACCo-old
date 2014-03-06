//===--- CGStmt.cc --------------------------------------------------------===//
//
//  ~~~ The C4 Compiler ~~~
//
//  This file implements the code generation for statements.
//
//===----------------------------------------------------------------------===//


#include "CodeGen.h"

#include "../AST/Decl.h"
#include "../AST/Expr.h"
#include "../AST/Stmt.h"


using namespace C4;
using namespace AST;
using namespace CodeGen;
using namespace llvm;


void IllegalStmt::emit( CodeGenFunction & ) const
{
  assert( false && "cannot emit code for illegal AST node" );
}

void ExprStmt::emit( CodeGenFunction &CGF ) const
{
  this->expr->emit( CGF );
}

void CaseStmt::emit( CodeGenFunction &CGF ) const
{
  assert( false && "not implemented yet" );
}

void LabelStmt::emit( CodeGenFunction &CGF ) const
{
  assert( false && "not implemented yet" );
}

void IfStmt::emit( CodeGenFunction &CGF ) const
{
  assert( false && "not implemented yet" );
}

void SwitchStmt::emit( CodeGenFunction &CGF ) const
{
  assert( false && "not implemented yet" );
}

void WhileStmt::emit( CodeGenFunction &CGF ) const
{
  assert( false && "not implemented yet" );
}

void DoStmt::emit( CodeGenFunction &CGF ) const
{
  assert( false && "not implemented yet" );
}

void ForStmt::emit( CodeGenFunction &CGF ) const
{
  assert( false && "not implemented yet" );
}

void BreakStmt::emit( CodeGenFunction &CGF ) const
{
  assert( false && "not implemented yet" );
}

void ContinueStmt::emit( CodeGenFunction &CGF ) const
{
  assert( false && "not implemented yet" );
}

void GotoStmt::emit( CodeGenFunction &CGF ) const
{
  assert( false && "not implemented yet" );
}

void ReturnStmt::emit( CodeGenFunction &CGF ) const
{
  assert( false && "not implemented yet" );
}

void BlockItem::emit( CodeGenFunction &CGF ) const
{
  if ( this->decl )
    this->decl->emit( CGF );
  else
    this->stmt->emit( CGF );
}

void CompoundStmt::emit( CodeGenFunction &CGF ) const
{
  // Emit all block items
  for ( auto it = begin(); it != end(); ++it )
  {
    (*it)->emit( CGF );
  }
}
