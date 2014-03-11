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
      notifyUses( InstrTopWorklist.pop_back_val() );
    if ( ! InstrWorklist.empty() )
      notifyUses( InstrWorklist.pop_back_val() );
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


//===----------------------------------------------------------------------===//
//
//  Helper Methods
//
//===----------------------------------------------------------------------===//

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

void SCCPSolver::notifyUses( Value * const V )
{
  /* NOTE: To only notify the reachable instructions, we can compute the
   * intersection of the keys of the ValueMap and the uses of the value V.
   */

  for ( auto U = V->use_begin(); U != V->use_end(); ++U )
    if ( Instruction *UI = dyn_cast< Instruction >( *U ) )
      if ( BBExecutable.count( UI->getParent() ) )
        visit( *UI );
}

void SCCPSolver::addToWorkList( Value * const V )
{
  /* Get the LatticeValue for V. */
  LatticeValue &LV = getLatticeValue( V );

  /* If the LV is TOP, add V to the priorized work list, otherwise add it to the
   * regular work list.
   */
  if ( LV.isTop() )
    InstrTopWorklist.push_back( V );
  else
    InstrWorklist.push_back( V );
}

void SCCPSolver::addToWorkList( BasicBlock * const BB )
{
  BBWorklist.push_back( BB );
  BBExecutable.insert( BB );
}


//===----------------------------------------------------------------------===//
//
//  Visit Methods
//
//===----------------------------------------------------------------------===//

void SCCPSolver::visitBinaryOperator( llvm::BinaryOperator &I )
{
  Value * const op1 = I.getOperand(0);
  Value * const op2 = I.getOperand(1);
  LatticeValue latticeValOp1 = getLatticeValue(op1);
  LatticeValue latticeValOp2 = getLatticeValue(op1);

  LatticeValue &currentResult = getLatticeValue(&I);
  LatticeValue newResult;
  if(latticeValOp1.isBottom() || latticeValOp2.isBottom())
  {
    newResult; //Bottom by default;
  }
  else if(latticeValOp1.isTop() || latticeValOp2.isTop())
  {
      newResult.setTop();
  }
  else
  {
      newResult.join(ConstantExpr::get(I.getOpcode(), latticeValOp1.getConstant(),
          latticeValOp2.getConstant()));
  }
  if(currentResult.join(newResult))
  {
    addToWorkList(&I);
  }
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
    lvI.join( ConstantExpr::getCompare( I.getPredicate(),
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
  /* Always assume top */
  LatticeValue lv = getLatticeValue( &I );
  lv.setTop();
  /* TODO notify users */
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

  /* If the LatticeValue changed, add this value to the work list. */
  if ( OldLV.join( LV ) )
    addToWorkList( &I );
}

void SCCPSolver::visitBranchInst( llvm::BranchInst &I )
{
  /* If we have an unconditional branch, the BB it's pointing to will be
   * reachable iff the BB containing this branch instruction is reachable.
   */
  if ( I.isUnconditional() )
  {
    if ( BBExecutable.count( I.getParent() ) )
      addToWorkList( I.getSuccessor( 0 ) );
    return;
  }

  /* If we have a conditional branch, we have to check the LatticeValue of it's
   * condition.
   */
  LatticeValue &CondLV = getLatticeValue( I.getCondition() );

  /* If the LV of the condition is BOTTOM, we assume the branch is never taken.
   */
  if ( CondLV.isBottom() )
    return;

  /* If CondLV is TOP, we assume both sides of the branch will be taken. */
  if ( CondLV.isTop() )
  {
    addToWorkList( I.getSuccessor( 0 ) );
    addToWorkList( I.getSuccessor( 1 ) );
    return;
  }

  /* If the condition is a constant, only one side of the branch is taken. */
  addToWorkList( I.getSuccessor( CondLV.getConstant()->isZeroValue() ) );
}

void SCCPSolver::visitReturnInst( llvm::ReturnInst &I )
{
  /* nothing to do here... */
}
