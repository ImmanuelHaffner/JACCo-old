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
  if ( ! Builder.GetInsertPoint()->isTerminator() )
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
  /* Iterate over all goto's, and then lookup its corresponding label and create
   * a branch.
   */
  for ( auto &it : gotoTargets )
  {
    /* Get the label for the goto. */
    auto elem = labels.find( it.first );
    if ( elem != labels.end() )
      assert( false && "unknown label, should be unreachable" );

    /* Create a branch from the goto block to the label block. */
    Builder.SetInsertPoint( it.second );
    Builder.CreateBr( elem->second );
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
