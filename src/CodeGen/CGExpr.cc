//===--- CGExpr.cc --------------------------------------------------------===//
//
//  ~~~ The C4 Compiler ~~~
//
//  This file implements the code generation for expressions.
//
//===----------------------------------------------------------------------===//


#include "CodeGen.h"

#include <cstring>
#include <vector>
#include "../Lex/Token.h"
#include "../AST/Expr.h"
#include "../AST/Type.h"
#include "../Support/Entity.h"


using namespace C4;
using namespace Lex;
using namespace AST;
using namespace Sema;
using namespace CodeGen;
using namespace llvm;


llvm::Value * IllegalExpr::emit( CodeGenFunction &, bool /* = false */ ) const
{
  assert( false && "cannot emit code for illegal AST node" );
  return NULL;
}

llvm::Value * ExprList::emit( CodeGenFunction &CGF,
    bool asLValue /* = false */ ) const
{
  if ( asLValue )
    assert( false && "cannot take LValue of an expression list" );

  /* Emit code for all expressions in the list, and return the value of the last
   * expression.
   */
  Value *result = NULL;
  for ( auto it = begin(); it != end(); ++it )
  {
    /* An expression list cannot be an LValue */
    result = (*it)->emit( CGF );
  }
  return result;
}

llvm::Value * Variable::emit( CodeGenFunction &CGF,
    bool asLValue /* = false */ ) const
{
  if ( asLValue )
    return getEntity()->value;  // returns the alloca of the variable
  return CGF.Builder.CreateLoad( getEntity()->value );  // returns the value
}

llvm::Value * AST::Constant::emit( CodeGenFunction &CGF,
    bool asLValue /* = false */ ) const
{
  if ( asLValue )
    assert( false && "cannot take LValue of a constant" );

  return CGF.Builder.getInt32( atoi( this->tok.sym.str() ) );
}

llvm::Value * StringLiteral::emit( CodeGenFunction &CGF,
    bool asLValue /* = false */ ) const
{
  if ( asLValue )
    assert( false && "cannot take LValue of a string literal" );

  /* Always build a string in a 'global' context. */
  return CGF.Builder.CreateGlobalStringPtr( this->tok.sym.str() );
}

llvm::Value * BinaryExpr::emit( CodeGenFunction &CGF,
    bool asLValue /* = false */ ) const
{
  if ( asLValue )
    assert( false && "cannot take LValue of a binary expression" );

  /* Emit code for the RHS and LHS, then compute the result, except for short
   * circuit evaluation.
   */

  switch ( this->tok.kind )
  {
    case TK::LAnd:
      {
        /* Create a basic block for the RHS. */
        BasicBlock *rhs = CGF.getBasicBlock( "LAnd.Rhs" );
        /* Create a basic block to merge control flow. */
        BasicBlock *end = CGF.getBasicBlock( "LAnd.End" );

        PHINode *phi = PHINode::Create( CGF.Builder.getInt1Ty(), 2, "LAnd.Phi" );

        /* Recursively emit code for the LHS. */
        CGF.Builder.CreateCondBr(
            CGF.EvaluateExprAsBool( this->lhs->emit( CGF ) ),
            rhs, end );
        phi->addIncoming( CGF.Builder.getInt1( false ),
            CGF.Builder.GetInsertBlock() );

        /* Recursively emit code for the RHS. */
        CGF.Builder.SetInsertPoint( rhs );
        Value *rhsV = CGF.EvaluateExprAsBool( this->rhs->emit( CGF ) );
        phi->addIncoming( rhsV, rhs );

        /* Emit the end block to merge control flow. */
        CGF.EmitBlock( end );
        CGF.Builder.Insert( phi );

        return phi;
      }

    case TK::LOr:
      {
        /* Create a basic block for the RHS. */
        BasicBlock *rhs = CGF.getBasicBlock( "LOr.Rhs" );
        /* Create a basic block to merge control flow. */
        BasicBlock *end = CGF.getBasicBlock( "LOr.End" );

        PHINode *phi = PHINode::Create( CGF.Builder.getInt1Ty(), 2, "LOr.Phi" );

        /* Recursively emit code for the LHS. */
        CGF.Builder.CreateCondBr(
            CGF.EvaluateExprAsBool( this->lhs->emit( CGF ) ),
            end, rhs );
        phi->addIncoming( CGF.Builder.getInt1( true ),
            CGF.Builder.GetInsertBlock() );

        /* Recursively emit code for the RHS. */
        CGF.Builder.SetInsertPoint( rhs );
        Value *rhsV = CGF.EvaluateExprAsBool( this->rhs->emit( CGF ) );
        phi->addIncoming( rhsV, rhs );

        /* Emit the end block to merge control flow. */
        CGF.EmitBlock( end );
        CGF.Builder.Insert( phi );

        return phi;
      }

    default:  // exit this switch
      break;
  } // end switch token kind

  Value *lhsV = this->lhs->emit( CGF );
  Value *rhsV = this->rhs->emit( CGF );

  /* cast if necessary */
  if ( lhsV->getType() != rhsV->getType() )
  {
    lhsV = CGF.GetAs( lhsV, CGF.Builder.getInt32Ty() );
    rhsV = CGF.GetAs( rhsV, CGF.Builder.getInt32Ty() );
  }

  switch ( this->tok.kind )
  {
    case Lex::TK::Mul:
      return CGF.Builder.CreateMul( lhsV, rhsV );

    case Lex::TK::Div:
      return CGF.Builder.CreateSDiv( lhsV, rhsV );

    case Lex::TK::Mod:
      return CGF.Builder.CreateSRem( lhsV, rhsV );

    case Lex::TK::Plus:
      return CGF.Builder.CreateAdd( lhsV, rhsV );

    case Lex::TK::Minus:
      return CGF.Builder.CreateSub( lhsV, rhsV );

    case Lex::TK::RShift:
      return CGF.Builder.CreateAShr( lhsV, rhsV );

    case Lex::TK::LShift:
      return CGF.Builder.CreateShl( lhsV, rhsV );

    case Lex::TK::Le:
      return CGF.Builder.CreateICmpSLT( lhsV, rhsV );

    case Lex::TK::Gr:
      return CGF.Builder.CreateICmpSGT( lhsV, rhsV );

    case Lex::TK::LEq:
      return CGF.Builder.CreateICmpSLE( lhsV, rhsV );

    case Lex::TK::GEq:
      return CGF.Builder.CreateICmpSGE( lhsV, rhsV );

    case Lex::TK::Eq:
      return CGF.Builder.CreateICmpEQ( lhsV, rhsV );

    case Lex::TK::NE:
      return CGF.Builder.CreateICmpNE( lhsV, rhsV );

    case Lex::TK::And:
      return CGF.Builder.CreateAnd( lhsV, rhsV );

    case Lex::TK::Xor:
      return CGF.Builder.CreateXor( lhsV, rhsV );

    case Lex::TK::Or:
      return CGF.Builder.CreateOr( lhsV, rhsV );

    default:
      assert( false && "unknown token kind" );
  } // end switch token kind

  return NULL;
}

llvm::Value * ConditionalExpr::emit( CodeGenFunction &CGF,
    bool asLValue /* = false */ ) const
{
  if ( asLValue )
    assert( false && "cannot take LValue of a conditional expression" );

  /* Create the BasicBlocks for the true, false, and end successor. */
  BasicBlock *trueBlock = CGF.getBasicBlock( "cond.true" );
  BasicBlock *falseBlock = CGF.getBasicBlock( "cond.false" );
  BasicBlock *endBlock = CGF.getBasicBlock( "cond.end" );

  /* Create the PHINode for the result. */
  llvm::Type *resType = this->lhs->getEntity()->type->getLLVMType( CGF );
  PHINode *phi = PHINode::Create( resType, 2, "cond.result" );

  Value *condV = CGF.EvaluateExprAsBool( this->cond->emit( CGF ) );

  CGF.Builder.CreateCondBr( condV, trueBlock, falseBlock );

  /* Emit the LHS. */
  CGF.Builder.SetInsertPoint( trueBlock );
  phi->addIncoming( this->lhs->emit( CGF ), CGF.Builder.GetInsertBlock() );
  CGF.EmitBlock( endBlock );

  /* Emit the RHS. */
  CGF.Builder.SetInsertPoint( falseBlock );
  phi->addIncoming( this->rhs->emit( CGF ), CGF.Builder.GetInsertBlock() );
  CGF.EmitBlock( endBlock );

  /* Emit the phi. */
  CGF.Builder.Insert( phi );
  return phi;
}

llvm::Value * AssignmentExpr::emit( CodeGenFunction &CGF,
    bool asLValue /* = false */ ) const
{
  if ( asLValue )
    assert( false && "cannot take LValue of an assignment expression" );

  /* The RHS must be evaluated first. */
  Value *rhsV = this->rhs->emit( CGF );

  /* Evaluate the LHS. */
  Value *lhsV = this->lhs->emit( CGF, /* asLValue = */ true );

  /* Get the type of the LHS (without ptr type). */
  llvm::Type *type = this->lhs->getEntity()->type->getLLVMType( CGF );

  CGF.Builder.CreateStore(
      CGF.GetAs( rhsV, type ),
      lhsV
      );

  return rhsV;
}

llvm::Value * UnaryOperation::emit( CodeGenFunction &CGF,
    bool asLValue /* = false */ ) const
{
  switch ( this->tok.kind )
  {
    case TK::And:
      assert( ! asLValue && "cannot take LValue of address operation" );
      return this->expr->emit( CGF, true );

    case TK::Mul:
      if ( asLValue )
        return this->expr->emit( CGF );
      return CGF.Builder.CreateLoad( this->expr->emit( CGF ) );

    case TK::Plus:
      return this->expr->emit( CGF );

    case TK::Minus:
      {
        /* -x == neg(x) + 1 */
        llvm::Type *type = this->expr->getEntity()->type->getLLVMType( CGF );
        return CGF.Builder.CreateAdd(
            CGF.Builder.CreateNeg(
              this->expr->emit( CGF ) ),
            ConstantInt::get( type, 0 ) );
      }

    case TK::Neg:
      return CGF.Builder.CreateNeg( this->expr->emit( CGF ) );

    case TK::Not:
      return CGF.Builder.CreateNot(
          CGF.EvaluateExprAsBool( this->expr->emit( CGF ) ) );

    default:
      break;
  }

  assert( false && "unknown unary operation, should be unreachable" );
  return NULL;
}

llvm::Value * SubscriptExpr::emit( CodeGenFunction &CGF,
    bool asLValue /* = false */ ) const
{
  if ( asLValue )
    assert( false && "cannot take LValue of a subscript expression" );

  /* Evaluate the LHS.  Must be of pointer type. */
  Value *arr = this->expr->emit( CGF );
  /* Evaluate the RHS.  Must be of integer type. */
  Value *pos = this->index->emit( CGF );

  Value *addr = CGF.Builder.CreateIntToPtr(
      CGF.Builder.CreateAdd(
        CGF.Builder.CreatePtrToInt( arr, pos->getType() ),
        pos ), arr->getType() );

  return CGF.Builder.CreateLoad( addr );
}

llvm::Value * DotExpr::emit( CodeGenFunction &CGF, bool asLValue /* = false */ )
  const
{
  assert( false && "not implemented yet" );
  return NULL;
}

llvm::Value * ArrowExpr::emit( CodeGenFunction &CGF,
    bool asLValue /* = false */ ) const
{
  assert( false && "not implemented yet" );
  return NULL;
}

llvm::Value * FunctionCall::emit( CodeGenFunction &CGF,
    bool asLValue /* = false */ ) const
{
  if ( asLValue )
    assert( false && "cannot take LValue of a function call" );

  /* Get the function. */
  llvm::Value *fun = CGF.M.getFunction( this->fun->tok.sym.str() );

  std::vector< llvm::Value * > args;

  ExprList const * const argList =
    static_cast< ExprList const * >( this->args );

  /* Store the RValues of all arguments. */
  for ( auto it = argList->begin(); it != argList->end(); ++it )
  {
    Value *argV = (*it)->emit( CGF );

    /* Skip Void Types */
    if ( argV->getType()->isVoidTy() )
      continue;

    args.push_back( argV );
  }
  
  return CGF.Builder.CreateCall( fun, args );
}

llvm::Value * PostIncExpr::emit( CodeGenFunction &CGF,
    bool asLValue /* = false */ ) const
{
  /* Get the LValue of the sub-expression. */
  Value *subV = this->expr->emit( CGF, true );

  /* Increment the value of the sub-expression by 1 and store the result. */
  Value *val = CGF.Builder.CreateLoad( subV );
  CGF.Builder.CreateStore( 
      CGF.Builder.CreateAdd(
        val,
        ConstantInt::get( val->getType(), 1 ) ),
      subV );

  if ( asLValue )
    return subV;
  return val;
}

llvm::Value * PostDecExpr::emit( CodeGenFunction &CGF,
    bool asLValue /* = false */ ) const
{
  /* Get the LValue of the sub-expression. */
  Value *subV = this->expr->emit( CGF, true );

  /* Decrement the value of the sub-expression by 1 and store the result. */
  Value *val = CGF.Builder.CreateLoad( subV );
  CGF.Builder.CreateStore( 
      CGF.Builder.CreateAdd(
        val,
        ConstantInt::get( val->getType(), -1 ) ),
      subV );

  if ( asLValue )
    return subV;
  return val;
}

llvm::Value * PreIncExpr::emit( CodeGenFunction &CGF,
    bool asLValue /* = false */ ) const
{
  /* Get the LValue of the sub-expression. */
  Value *subV = this->expr->emit( CGF, true );

  /* Increment the value of the sub-expression by 1 and store the result. */
  Value *val = CGF.Builder.CreateLoad( subV );
  val = CGF.Builder.CreateAdd( val,
      ConstantInt::get( val->getType(), 1 ) );
  CGF.Builder.CreateStore( val, subV );

  if ( asLValue )
    return subV;
  return val;
}

llvm::Value * PreDecExpr::emit( CodeGenFunction &CGF,
    bool asLValue /* = false */ ) const
{
  /* Get the LValue of the sub-expression. */
  Value *subV = this->expr->emit( CGF, true );

  /* Decrement the value of the sub-expression by 1 and store the result. */
  Value *val = CGF.Builder.CreateLoad( subV );
  val = CGF.Builder.CreateAdd( val,
      ConstantInt::get( val->getType(), -1 ) );
  CGF.Builder.CreateStore( val, subV );

  if ( asLValue )
    return subV;
  return val;
}

llvm::Value * SizeofExpr::emit( CodeGenFunction &CGF,
    bool asLValue /* = false */ ) const
{
  /* if we have a string literal, compute its length */
  if ( dynamic_cast< StringLiteral const * >( this->expr ) )
    return CGF.Builder.getInt32(
        strlen( this->expr->tok.sym.str() ) - 2 /* the quotes */ );

  /* Emit code for the sub-expression.  This is necessary, since it may have
   * side effects.
   */
  this->expr->emit( CGF );

  /* Compute the type of the sub-expression. */
  Sema::Type const * const type = this->expr->getEntity()->type;

  if ( dynamic_cast< Sema::FuncType const * >( type ) )
    return CGF.Builder.getInt32( 4 );

  auto ot = static_cast< Sema::ObjType const * >( type );
  return CGF.Builder.getInt32( ot->size() );
}

llvm::Value * SizeofTypeExpr::emit( CodeGenFunction &CGF,
    bool /* = false */ ) const
{
  /* Get the type of sub-node. */
  Sema::ObjType const * const type =
    static_cast< Sema::ObjType const * >( this->typeName->getEntity()->type );
  return CGF.Builder.getInt32( type->size() );
}
