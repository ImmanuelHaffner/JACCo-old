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

void CaseStmt::emit( CodeGenFunction & ) const
{
  assert( false && "not implemented yet" );
}

void LabelStmt::emit( CodeGenFunction &CGF ) const
{
  Twine name( "label." );
  name.concat( this->tok.sym.str() );
  BasicBlock * labelBlock = CGF.getBasicBlock( name );
  CGF.EmitBlock( labelBlock );

  // Add entry to label/block map of current function
  CGF.addLabel( this->tok.sym, labelBlock );
}

void IfStmt::emit( CodeGenFunction &CGF ) const
{
  BasicBlock * thenBlock = CGF.getBasicBlock( "if.then" );
  BasicBlock * elseBlock = CGF.getBasicBlock( "if.else" );
  BasicBlock * endBlock = CGF.getBasicBlock( "if.end" );

  Value *condV = CGF.EvaluateExprAsBool( this->Cond->emit( CGF ) );
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

void SwitchStmt::emit( CodeGenFunction & ) const
{
  assert( false && "not implemented yet" );
}

void WhileStmt::emit( CodeGenFunction &CGF ) const
{
  BasicBlock * condBlock = CGF.getBasicBlock( "while.cond" );
  BasicBlock * bodyBlock = CGF.getBasicBlock( "while.body" );
  BasicBlock * exitBlock = CGF.getBasicBlock( "while.end" );

  CGF.pushJumpTarget( JumpTarget( exitBlock, condBlock ) ); 

  /* Emit the condition block. */
  CGF.EmitBlock( condBlock );
  Value *condV = CGF.EvaluateExprAsBool( this->Cond->emit( CGF ) );
  CGF.Builder.CreateCondBr( condV, bodyBlock, exitBlock );

  /* Emit the body block. */
  CGF.Builder.SetInsertPoint( bodyBlock );
  this->Body->emit( CGF );
  CGF.Builder.CreateBr( condBlock );

  CGF.Builder.SetInsertPoint( exitBlock );
  CGF.popJumpTarget();
}

void DoStmt::emit( CodeGenFunction & ) const
{
  assert( false && "not implemented yet" );
}

void ForStmt::emit( CodeGenFunction & ) const
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
  CGF.addGoto( this->tok.sym, CGF.Builder.GetInsertBlock() );
  CGF.Builder.SetInsertPoint( CGF.getBasicBlock() );
}

void ReturnStmt::emit( CodeGenFunction &CGF ) const
{
  if ( this->expr )
  {
    Value *exprV = this->expr->emit( CGF );
    CGF.Builder.CreateRet( exprV );
  }
  else
    CGF.Builder.CreateRetVoid();
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
