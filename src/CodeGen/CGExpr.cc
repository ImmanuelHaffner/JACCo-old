//===--- CGExpr.cc --------------------------------------------------------===//
//
//  ~~~ The C4 Compiler ~~~
//
//  This file implements the code generation for expressions.
//
//===----------------------------------------------------------------------===//


#include "CodeGen.h"

#include "../AST/Expr.h"
#include "../Support/Entity.h"


using namespace C4;
using namespace AST;
using namespace Sema;
using namespace CodeGen;
using namespace llvm;


llvm::Value * IllegalExpr::emit( CodeGenFunction &CGF ) const
{
  assert( false && "cannot emit code for illegal AST node" );
}

llvm::Value * ExprList::emit( CodeGenFunction &CGF ) const
{
  assert( false && "not implemented yet" );
}

llvm::Value * Variable::emit( CodeGenFunction &CGF ) const
{
  return getEntity()->value;
}

llvm::Value * AST::Constant::emit( CodeGenFunction &CGF ) const
{
  return CGF.Builder.getInt32( atoi( this->tok.sym.str() ) );
}

llvm::Value * StringLiteral::emit( CodeGenFunction &CGF ) const
{
  /* Always build a string in a 'global' context. */
  return CGF.Builder.CreateGlobalStringPtr( this->tok.sym.str() );
}

llvm::Value * BinaryExpr::emit( CodeGenFunction &CGF ) const
{
  assert( false && "not implemented yet" );
}

llvm::Value * ConditionalExpr::emit( CodeGenFunction &CGF ) const
{
  assert( false && "not implemented yet" );
}

llvm::Value * AssignmentExpr::emit( CodeGenFunction &CGF ) const
{
  /* Create the assignment expression. The RHS must be evaluated first. */
  return CGF.Builder.CreateStore( this->rhs->emit( CGF ),
      this->lhs->emit( CGF ) );
}

llvm::Value * UnaryOperation::emit( CodeGenFunction &CGF ) const
{
  assert( false && "not implemented yet" );
}

llvm::Value * SubscriptExpr::emit( CodeGenFunction &CGF ) const
{
  assert( false && "not implemented yet" );
}

llvm::Value * DotExpr::emit( CodeGenFunction &CGF ) const
{
  assert( false && "not implemented yet" );
}

llvm::Value * ArrowExpr::emit( CodeGenFunction &CGF ) const
{
  assert( false && "not implemented yet" );
}

llvm::Value * FunctionCall::emit( CodeGenFunction &CGF ) const
{
  assert( false && "not implemented yet" );
}

llvm::Value * PostIncExpr::emit( CodeGenFunction &CGF ) const
{
  assert( false && "not implemented yet" );
}

llvm::Value * PostDecExpr::emit( CodeGenFunction &CGF ) const
{
  assert( false && "not implemented yet" );
}

llvm::Value * PreIncExpr::emit( CodeGenFunction &CGF ) const
{
  assert( false && "not implemented yet" );
}

llvm::Value * PreDecExpr::emit( CodeGenFunction &CGF ) const
{
  assert( false && "not implemented yet" );
}

llvm::Value * SizeofExpr::emit( CodeGenFunction &CGF ) const
{
  assert( false && "not implemented yet" );
}

llvm::Value * SizeofTypeExpr::emit( CodeGenFunction &CGF ) const
{
  assert( false && "not implemented yet" );
}
