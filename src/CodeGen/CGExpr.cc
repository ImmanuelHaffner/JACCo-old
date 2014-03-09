//===--- CGExpr.cc --------------------------------------------------------===//
//
//  ~~~ The C4 Compiler ~~~
//
//  This file implements the code generation for expressions.
//
//===----------------------------------------------------------------------===//


#include "CodeGen.h"

#include <algorithm>
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
  /* Get the entitiy. */
  Entity * const entity = this->getEntity();

  /* Get its value. */
  Value *val = entity->value;

  /* If we have a function, cast it to a i8* function pointer. */
  if ( dynamic_cast< Sema::FuncType const * >( entity->type ) )
    return CGF.Builder.CreateBitCast( val, CGF.Builder.getInt8PtrTy() );

  if ( asLValue )
    return val;  // returns the alloca of the variable
  return CGF.Builder.CreateLoad( val );  // returns the value
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

  /* Get the string without the quotes. */
  std::string s( this->tok.sym.str() );

  /* Always build a string in a 'global' context.  Take the substring without
   * the quotes.
   */
  return CGF.Builder.CreateGlobalStringPtr( s.substr( 1, s.size() - 2 ) );
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


  /* Emit both the LHS and the RHS. */
  Value *lhsV = this->lhs->emit( CGF );
  Value *rhsV = this->rhs->emit( CGF );

  /* Get the type of both the LHS and the RHS, and also for the return type. */
  llvm::Type *lhsTy = lhsV->getType();
  llvm::Type *rhsTy = rhsV->getType();

  /* Get the default return type. */
  llvm::Type *resTy = CGF.Builder.getInt32Ty();
  if ( lhsTy->isPointerTy() )
    resTy = lhsTy;
  else if ( rhsTy->isPointerTy() )
    resTy = rhsTy;
  else if ( lhsTy == rhsTy )
    resTy = lhsTy;

  switch ( this->tok.kind )
  {
    default:
      assert( false && "unknown token kind" );

    case Lex::TK::Mul:
      return CGF.Builder.CreateMul(
          CGF.GetAs( lhsV, resTy ),
          CGF.GetAs( rhsV, resTy ) );

    case Lex::TK::Div:
      return CGF.Builder.CreateSDiv(
          CGF.GetAs( lhsV, resTy ),
          CGF.GetAs( rhsV, resTy ) );

    case Lex::TK::Mod:
      return CGF.Builder.CreateSRem(
          CGF.GetAs( lhsV, resTy ),
          CGF.GetAs( rhsV, resTy ) );

    case Lex::TK::Plus:
      if ( lhsTy->isPointerTy() )
        return CGF.Builder.CreateGEP( lhsV, rhsV );
      if ( rhsTy->isPointerTy() )
        return CGF.Builder.CreateGEP( rhsV, lhsV );
      return CGF.Builder.CreateAdd(
          CGF.GetAs( lhsV, resTy ),
          CGF.GetAs( rhsV, resTy ) );

    case Lex::TK::Minus:
      if ( lhsTy->isPointerTy() )
      {
        if ( rhsTy->isPointerTy() )
          return CGF.Builder.CreateSub(
                CGF.GetAs( lhsV, CGF.Builder.getInt32Ty() ),
                CGF.GetAs( rhsV, CGF.Builder.getInt32Ty() ) );
        return CGF.Builder.CreateGEP( lhsV, CGF.Builder.CreateNeg( rhsV ) );
      }
      return CGF.Builder.CreateSub(
          CGF.GetAs( lhsV, resTy ),
          CGF.GetAs( rhsV, resTy ) );

    case Lex::TK::RShift:
      return CGF.Builder.CreateAShr(
          CGF.GetAs( lhsV, resTy ),
          CGF.GetAs( rhsV, resTy ) );

    case Lex::TK::LShift:
      return CGF.Builder.CreateShl(
          CGF.GetAs( lhsV, resTy ),
          CGF.GetAs( rhsV, resTy ) );

    case Lex::TK::Le:
      return CGF.Builder.CreateICmpSLT(
          CGF.GetAs( lhsV, resTy ),
          CGF.GetAs( rhsV, resTy ) );

    case Lex::TK::Gr:
      return CGF.Builder.CreateICmpSGT(
          CGF.GetAs( lhsV, resTy ),
          CGF.GetAs( rhsV, resTy ) );

    case Lex::TK::LEq:
      return CGF.Builder.CreateICmpSLE(
          CGF.GetAs( lhsV, resTy ),
          CGF.GetAs( rhsV, resTy ) );

    case Lex::TK::GEq:
      return CGF.Builder.CreateICmpSGE(
          CGF.GetAs( lhsV, resTy ),
          CGF.GetAs( rhsV, resTy ) );

    case Lex::TK::Eq:
      return CGF.Builder.CreateICmpEQ(
          CGF.GetAs( lhsV, resTy ),
          CGF.GetAs( rhsV, resTy ) );

    case Lex::TK::NE:
      return CGF.Builder.CreateICmpNE(
          CGF.GetAs( lhsV, resTy ),
          CGF.GetAs( rhsV, resTy ) );

    case Lex::TK::And:
      return CGF.Builder.CreateAnd(
          CGF.GetAs( lhsV, resTy ),
          CGF.GetAs( rhsV, resTy ) );

    case Lex::TK::Xor:
      return CGF.Builder.CreateXor(
          CGF.GetAs( lhsV, resTy ),
          CGF.GetAs( rhsV, resTy ) );

    case Lex::TK::Or:
      return CGF.Builder.CreateOr(
          CGF.GetAs( lhsV, resTy ),
          CGF.GetAs( rhsV, resTy ) );
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

  /* Get the type of the LHS (without ptr type since its an LValue). */
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
      {
        Value *ptr = this->expr->emit( CGF );
        if ( asLValue )
          return ptr;

        /* If ptr is not of pointer type, cast it to a pointer with the type of
         * the sub-expr.
         */
        if ( ! ptr->getType()->isPointerTy() )
          ptr = CGF.GetAs( ptr,
              this->expr->getEntity()->type->getLLVMType( CGF ) );
        return CGF.Builder.CreateLoad( ptr );
      }

    case TK::Plus:
      return this->expr->emit( CGF );

    case TK::Minus:
        return CGF.Builder.CreateNeg( this->expr->emit( CGF ) );

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

  /* Compute the address to load. */
  Instruction *addr = GetElementPtrInst::Create( arr, pos );
  CGF.Builder.Insert( addr );

  /* Load the value from that address. */
  return CGF.Builder.CreateLoad( addr );
}

llvm::Value * DotExpr::emit( CodeGenFunction &CGF, bool asLValue /* = false */ )
  const
{
  //Find index of member in structure.
  Sema::StructType const *structType =
      dynamic_cast<Sema::StructType const*>(this->expr->getEntity()->type);
  auto elem = structType->indices.find(this->id.sym);
  if(elem == structType->indices.end())
  {
    assert(false && "Invalid member of struct.");
    return NULL;
  }
  int elemIndex = elem->second;

  //Store the address of this member in entity.
  Value *baseAddress = this->expr->emit(CGF, true);
  std::vector<Value *> gepParams;
  gepParams.push_back(CGF.Builder.getInt32(0));
  gepParams.push_back(CGF.Builder.getInt32(elemIndex));
  Value *addr =
      CGF.Builder.CreateInBoundsGEP(baseAddress, gepParams);

  this->getEntity()->value= addr;
  if(asLValue)
    return addr;
  return CGF.Builder.CreateLoad( addr );
}

llvm::Value * ArrowExpr::emit( CodeGenFunction &CGF,
    bool asLValue /* = false */ ) const
{
  //Find index of member in structure.
  Sema::PtrType const *ptrType =
      dynamic_cast<Sema::PtrType const *>(this->expr->getEntity()->type);
  Sema::StructType const *structType =
      dynamic_cast<Sema::StructType const *>(ptrType->innerType);
  auto elem = structType->indices.find(this->id.sym);
  if(elem == structType->indices.end())
  {
    assert(false && "Invalid member of struct.");
    return NULL;
  }
  int elemIndex = elem->second;

  //Store the address of this member in entity.
  Value *baseAddress = this->expr->emit(CGF, false);
  std::vector<Value *> gepParams;
  gepParams.push_back(CGF.Builder.getInt32(0));
  gepParams.push_back(CGF.Builder.getInt32(elemIndex));
  Value *addr =
      CGF.Builder.CreateInBoundsGEP(baseAddress, gepParams);

  this->getEntity()->value= addr;
  if(asLValue)
    return addr;
  return CGF.Builder.CreateLoad( addr );
}

llvm::Value * FunctionCall::emit( CodeGenFunction &CGF,
    bool asLValue /* = false */ ) const
{
  if ( asLValue )
    assert( false && "cannot take LValue of a function call" );

  /* Get the function. */
  llvm::Value *funcPtr = this->fun->getEntity()->value;

  /* If we have an alloca of a function pointer, and not a function pointer
   * itself, we need to emit a load first.
   */
  if ( dyn_cast< llvm::AllocaInst >( funcPtr ) )
    funcPtr = CGF.Builder.CreateLoad( funcPtr );

  /* Get the type of the function (without the pointer). */
  llvm::FunctionType *funcTy = NULL;
  if ( ( funcTy = dyn_cast< FunctionType >(
        funcPtr->getType()->getPointerElementType() ) ) );
  else if ( ( funcTy = dyn_cast< FunctionType >( funcPtr->getType() ) ) );
  else
  {
    funcPtr->dump();
    funcPtr->getType()->dump();
    std::cout << std::endl;
    assert( false && "not a function type" );
  }

  /* Collect the arguments for the function call. */
  std::vector< llvm::Value * > args;
  ExprList const * const argList =
    static_cast< ExprList const * >( this->args );

  /* Store the RValues of all arguments. */
  {
    auto argIt = argList->begin();
    auto paramN = 0;
    for ( ; argIt != argList->end(); ++argIt, ++paramN )
    {
      Value *argV = (*argIt)->emit( CGF );

      /* Skip Void Types */
      if ( argV->getType()->isVoidTy() )
        continue;

      args.push_back( CGF.GetAs( argV, funcTy->getParamType( paramN ) ) );
      //args.push_back( argV );
    }
  }

  return CGF.Builder.CreateCall( funcPtr, args );
}

static llvm::Value * EmitPreArithmExpr( CodeGenFunction &CGF,
    llvm::Value *ptr, bool asLValue, int step )
{
  /* Get the RValue of ptr. */
  Value *val = CGF.Builder.CreateLoad( ptr );

  if ( val->getType()->isPointerTy() )
    val = CGF.Builder.CreateGEP( val, CGF.Builder.getInt32( step ) );
  else
    val = CGF.Builder.CreateAdd( val,
        ConstantInt::get( val->getType(), step ) );

  CGF.Builder.CreateStore( val, ptr );

  if ( asLValue )
    return ptr;
  return val;
}

static llvm::Value * EmitPostArithmExpr( CodeGenFunction &CGF,
    Value *ptr, bool asLValue, int step )
{
  /* Get the RValue of ptr.  This is the value we will return. */
  Value *ret = CGF.Builder.CreateLoad( ptr );
  /* Create a copy of the value, so that we can modify and store it. */
  Value *val = ret;

  if ( ret->getType()->isPointerTy() )
    val = CGF.Builder.CreateGEP( val, CGF.Builder.getInt32( step ) );
  else
    val = CGF.Builder.CreateAdd( val,
        ConstantInt::get( val->getType(), step ) );

  /* Store the computed value. */
  CGF.Builder.CreateStore( val, ptr );

  if ( asLValue )
    return ptr;
  return ret;
}

llvm::Value * PostIncExpr::emit( CodeGenFunction &CGF,
    bool asLValue /* = false */ ) const
{
  return EmitPostArithmExpr( CGF, this->expr->emit( CGF, true ), asLValue, 1 );
}

llvm::Value * PostDecExpr::emit( CodeGenFunction &CGF,
    bool asLValue /* = false */ ) const
{
  return EmitPostArithmExpr( CGF, this->expr->emit( CGF, true ), asLValue, -1 );
}

llvm::Value * PreIncExpr::emit( CodeGenFunction &CGF,
    bool asLValue /* = false */ ) const
{
  return EmitPreArithmExpr( CGF, this->expr->emit( CGF, true ), asLValue, 1 );
}

llvm::Value * PreDecExpr::emit( CodeGenFunction &CGF,
    bool asLValue /* = false */ ) const
{
  return EmitPreArithmExpr( CGF, this->expr->emit( CGF, true ), asLValue, -1 );
}

llvm::Value * SizeofExpr::emit( CodeGenFunction &CGF,
    bool asLValue /* = false */ ) const
{
  assert( ! asLValue && "cannot take LValue of sizeof expression" );

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
    bool asLValue /* = false */ ) const
{
  assert( ! asLValue && "cannot take LValue of sizeof expression" );

  /* Get the type of sub-node. */
  Sema::ObjType const * const type =
    static_cast< Sema::ObjType const * >( this->typeName->getEntity()->type );
  return CGF.Builder.getInt32( type->size() );
}
