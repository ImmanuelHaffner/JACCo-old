#include "SCCPSolver.h"

#include "llvm/IR/Value.h"
#include "llvm/IR/Constants.h"


using namespace C4;
using namespace llvm;
using namespace Optimize;


void SCCPSolver::solve( Function *F )
{
  /* Add first basic block to worklist. */
  markBlockVisitable( F->begin() );

  /* Consider all arguments as top. */
  for ( Function::arg_iterator AI = F->arg_begin(); AI != F->arg_end(); ++AI )
    markTop(AI);

  /* Process elements until all work lists are empty. */
  while ( ! BBWorklist.empty() || ! InstrTopWorklist.empty() ||
      ! InstrWorklist.empty() )
  {
    /* Process the elements of the top work list first, to propagate TOP faster.
     * This will speed up finding a fixed point.
     */
    while ( ! InstrTopWorklist.empty() )
    {
      Value *I = InstrTopWorklist.pop_back_val();

      /* Visit every instruction using the value I. */
      for ( auto U = I->use_begin(); U != I->use_end(); ++U )
        if ( Instruction *UI = dyn_cast< Instruction >( *U ) )
          if ( BBExecutable.count( UI->getParent() ) )
              visit( *UI );
    }
    if ( ! InstrWorklist.empty() )
    {
      Value *I = InstrWorklist.pop_back_val();

      /* Visit every instruction using the value I. */
      for ( auto U = I->use_begin(); U != I->use_end(); ++U )
        if ( Instruction *UI = dyn_cast< Instruction >( *U ) )
          if ( BBExecutable.count( UI->getParent() ) )
              visit( *UI );
    }
    else
    {
      BasicBlock *elem = BBWorklist.pop_back_val();

      /* Notify all instructions in this basic block that they are newly
       * executable.
       */
      visit( elem );
    }
  }

  /* At this point we reached a fixed point. */

}

void SCCPSolver::markTop( llvm::Value *V )
{
  ValueMap[ V ].setTop();
}

void SCCPSolver::markBlockVisitable ( llvm::BasicBlock *BB )
{
  BBExecutable.insert( BB );
}

LatticeValue & SCCPSolver::getLatticeValue( Value * const V )
{
  assert ( V->getType()->isIntegerTy() && "only track values of integer type" );

  /* Get the LatticeValue for V.  If V was not already a key for the map, it
   * will immediately be inserted and mapped to BOTTOM.
   */
  auto it = ValueMap.insert( std::make_pair( V, LatticeValue() ) );
  LatticeValue &lv = it.first->second;

  /* If the key has not been mapped so far, we now check whether we have a real
   * constant.  If we have a contant, we raise the LatticeValue from BOTTOM to
   * CONSTANT, otherwise we leave it BOTTOM.
   */
  if ( it.second )
  {
    /* V wasn't a key in the map before.  Now check whether V is a defined
     * constant.
     */
    if ( Constant * const C = dyn_cast< Constant >( V ) )
      if ( ! isa< UndefValue >( C ) )
        /* Lift the LatticeValue from BOTTOM to CONSTANT. */
        lv.join( C );
  }

  return lv;
}


//===----------------------------------------------------------------------===//
//
//  Visit Methods
//
//===----------------------------------------------------------------------===//

void SCCPSolver::visitBinaryOperator( llvm::BinaryOperator &I )
{
  /* TODO: Implement */
  assert( false && "not implemented yet" );
}

void SCCPSolver::visitCallInst( llvm::CallInst &I )
{
  /* Always assume top */
  LatticeValue lv = getLatticeValue( &I );
  lv.setTop();
  /* TODO: Notify users */
}

void SCCPSolver::visitCastInst( llvm::CastInst &I )
{
  LatticeValue lvI = getLatticeValue( &I );

  if ( lvI.isTop() )
    return;

  LatticeValue lvOp = getLatticeValue( I.getOperand( 0 ) );

  /* Propagate child information */
  lvI.join( lvOp );
}

void SCCPSolver::visitICmpInst( llvm::ICmpInst &I )
{
  LatticeValue lvI = getLatticeValue ( &I );

  if ( lvI.isTop() )
    /* We can leave here as nothing will change */
    return;

  LatticeValue lvOp1 = getLatticeValue( I.getOperand( 0 ) );
  LatticeValue lvOp2 = getLatticeValue( I.getOperand( 1 ) );

  if ( lvOp1.isTop() || lvOp2.isTop() )
    /* TODO set to top and notify users */
    ;

  if ( lvOp1.isConstant() && lvOp2.isConstant() )
  {
    /* Set result to constant */
    lvI.setConstant( ConstantExpr::getCompare( I.getPredicate(),
        lvOp1.getConstant(), lvOp2.getConstant() ) );
    /* TODO notify users */
  }
}

void SCCPSolver::visitLoadInst( llvm::LoadInst &I )
{
  /* Always assume top */
  LatticeValue lv = getLatticeValue( &I );
  lv.setTop();
  /* TODO notify users */
}

void SCCPSolver::visitStoreInst( llvm::StoreInst &I )
{
  /* TODO: Implement */
  assert( false && "not implemented yet" );
}

void SCCPSolver::visitPHINode( llvm::PHINode &I )
{
  /* Get the current lattice value. */
  LatticeValue &OldLV = getLatticeValue( &I );

  /* If we already reached top, it can't get better.  Skip! */
  if ( OldLV.isTop() ) 
    return;
  
  /* Iterate over all incoming edges and try to infer a common constant.  As
   * soon as we hit TOP, we stop.
   */
  LatticeValue LV;
  for ( auto itBB = I.block_begin(); ! LV.isTop() && itBB != I.block_end();
      ++itBB )
  {
    /* If a block is not reachable, ignore it. */
    if ( BBExecutable.count( *itBB ) )
      continue;

    /* Join the LatticeValue from the incoming edge with our loop-LV. */
    LV.join( getLatticeValue( I.getIncomingValueForBlock( *itBB ) ) );
  }

  return OldLV.join( LV );
}

void SCCPSolver::visitBranchInst( llvm::BranchInst &I )
{
  /* TODO: Implement */
  assert( false && "not implemented yet" );
}

void SCCPSolver::visitReturnInst( llvm::ReturnInst &I )
{
  /* TODO: Implement */
  assert( false && "not implemented yet" );
}
