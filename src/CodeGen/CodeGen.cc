//===--- CodeGen.cc -------------------------------------------------------===//
//
//  ~~~ The C4 Compiler ~~~
//
//  This file implements the code gen function class and other more general
//  parts of the code gen.
//
//===----------------------------------------------------------------------===//


#include "CodeGen.h"

#include "../AST/AST.h"
#include "../Sema/TypeFactory.h"


using namespace C4;
using namespace AST;
using namespace Sema;
using namespace CodeGen;
using namespace llvm;


void TranslationUnit::emit( CodeGenFunction &CGF ) const
{
  /* Emit code for all external declarations. */
  for ( auto it = begin(); it != end(); ++it )
    (*it)->emit( CGF, /* isGlobal = */ true );
}

void CodeGenFunction::EmitBlock( BasicBlock * const target )
{
  if ( ! Builder.GetInsertBlock()->getTerminator() )
    Builder.CreateBr( target );
  Builder.SetInsertPoint( target );
}

BasicBlock * CodeGenFunction::getBasicBlock( Twine const &Name /* = "" */ )
{
  assert( parent && "cannot create a basic block without a parent" );
  return BasicBlock::Create( Context, Name, parent );
}

void CodeGenFunction::WireLabels()
{
  /* Iterate over all gotos, and then lookup its corresponding label and create
   * a branch.
   */
  for ( auto &Goto : gotoTargets )
  {
    /* Get the label for the goto. */
    auto Label = labels.find( Goto.first );
    if ( Label == labels.end() )
      assert( false && "unknown label, should be unreachable" );

    /* Go to the basic block of the goto stmt. */
    Builder.SetInsertPoint( Goto.second );
    /* Emit a branch from the goto BB to the label's BB. */
    Builder.CreateBr( Label->second );
  }

  /* Clear the gotos and labels for the next function definition. */
  gotoTargets.clear();
  labels.clear();
}

Value * CodeGenFunction::EvaluateExprAsBool( Value *expr )
{
  llvm::Type *type = expr->getType();

  /* If we already have a bool, stop here. */
  if ( type == Builder.getInt1Ty() )
    return expr;

  if ( type->isPointerTy() )
  {
    /* Check whether we have a NULL pointer. */
    return Builder.CreateIsNull( expr );
  }
  else
  {
    /* Compare the value of the expression to 0. */
    return Builder.CreateICmpNE( expr, ConstantInt::get( type, 0 ) );
  }
}

llvm::Value * CodeGenFunction::GetAs( llvm::Value *val, llvm::Type *type )
{
  /* If the types are equal, don't do anything and return val. */
  if ( val->getType() == type )
    return val;

  if ( type->isPointerTy() )
  {
    /* If val is a function, and type is a pointer type, return a bit-casted
     * function pointer.
     */
    if ( auto fun = dyn_cast< Function >( val ) )
      return ConstantExpr::getBitCast( fun, type );

    /* If we have a pointer, bit-cast it to the target pointer type. */
    if ( val->getType()->isPointerTy() )
      return Builder.CreateBitCast( val, type );

    /* If we have an integer and want a pointer, create a IntToPtr cast. */
    if ( val->getType()->isIntegerTy() )
      return Builder.CreateIntToPtr( val, type );
  } // end type->isPointerTy()
  else if ( type->isIntegerTy() )
  {
    /* If we have a pointer and want an integer, create a IntToPtr cast. */
    if ( val->getType()->isPointerTy() )
      return Builder.CreatePtrToInt( val, type );

    /* If we have an integer, and want a integer of different size, we have to
     * extend or trunc.
     */
    if ( val->getType()->isIntegerTy() )
    {
      /* Bool (i1) and char (i8) values have to be zero extended. */
      if ( val->getType() == Builder.getInt1Ty() ||
          val->getType() == Builder.getInt8Ty() )
        return Builder.CreateZExt( val, type );

      /* Regular integer types will be sign extended or truncated. */
      return Builder.CreateSExtOrTrunc( val, type );
    }
  } // end type->isIntegerTy()

  val->dump();
  type->dump();
  assert( false && "GetAs not supported for this case" );
  return NULL;
}
