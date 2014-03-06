//===--- CGExpr.cc --------------------------------------------------------===//
//
//  ~~~ The C4 Compiler ~~~
//
//  This file implements the code generation for expressions.
//
//===----------------------------------------------------------------------===//


#include "CodeGen.h"

#include "../AST/Expr.h"


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
  assert( false && "not implemented yet" );
}

llvm::Value * AST::Constant::emit( CodeGenFunction &CGF ) const
{
  assert( false && "not implemented yet" );
}

llvm::Value * StringLiteral::emit( CodeGenFunction &CGF ) const
{
  assert( false && "not implemented yet" );
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
  assert( false && "not implemented yet" );
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
