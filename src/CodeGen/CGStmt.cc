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
  Value * condV = this->Cond->emit( CGF );
  BasicBlock * thenBlock = BasicBlock::Create( CGF.Context, "if.then" );
  BasicBlock * elseBlock = BasicBlock::Create( CGF.Context, "if.else" );
  BasicBlock * endBlock = BasicBlock::Create( CGF.Context, "if.end" );
  CGF.Builder.CreateCondBr( condV, thenBlock, elseBlock );
 
  CGF.Builder.SetInsertPoint( thenBlock );
  this->Then->emit( CGF );
  CGF.Builder.CreateBr( endBlock );

  if ( Else )
  {
    CGF.Builder.SetInsertPoint( elseBlock );
    this->Else->emit( CGF );
    CGF.Builder.CreateBr( endBlock );
  }

  CGF.Builder.SetInsertPoint( endBlock );
}

void SwitchStmt::emit( CodeGenFunction &CGF ) const
{
  assert( false && "not implemented yet" );
}

void WhileStmt::emit( CodeGenFunction &CGF ) const
{
  Value * condV = this->Cond->emit( CGF );
  BasicBlock * bodyBlock = BasicBlock::Create( CGF.Context, "while.body" );
  BasicBlock * condBlock = BasicBlock::Create( CGF.Context, "while.cond" );
  BasicBlock * exitBlock = BasicBlock::Create( CGF.Context, "while.end" );

  CGF.pushJumpTarget( JumpTarget( exitBlock, condBlock ) ); 

  CGF.Builder.CreateBr( condBlock );
  CGF.Builder.SetInsertPoint( condBlock );
  CGF.Builder.CreateCondBr( condV, bodyBlock, exitBlock );

  CGF.Builder.SetInsertPoint( bodyBlock );
  this->Body->emit( CGF );
  CGF.Builder.CreateBr( condBlock );

  CGF.Builder.SetInsertPoint( exitBlock );
  CGF.popJumpTarget();
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
  CGF.Builder.CreateBr( CGF.getCurrentJumpTarget().breakTarget );
}

void ContinueStmt::emit( CodeGenFunction &CGF ) const
{
  CGF.Builder.CreateBr( CGF.getCurrentJumpTarget().continueTarget );
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
