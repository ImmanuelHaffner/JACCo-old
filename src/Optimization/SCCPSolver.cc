#include "SCCPSolver.h"

#include "llvm/IR/Value.h"
#include "llvm/IR/Constants.h"


using namespace C4;
using namespace llvm;
using namespace Optimize;


void SCCPSolver::runOnFunction( Function &F )
{
  SCCPSolver Solver;

  /* Add first basic block to worklist. */
  Solver.addToWorkList( F.begin() );

  /* Consider all arguments as top. */
  for ( Function::arg_iterator AI = F.arg_begin(); AI != F.arg_end(); ++AI )
    Solver.markTop(AI);

  Solver.solve();
}

void SCCPSolver::solve()
{
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
    else if ( ! BBWorklist.empty() )
    {
      BasicBlock *elem = BBWorklist.pop_back_val();

      /* Notify all instructions in this basic block that they are newly
       * executable.
       */
      visit( elem );
    }
  }
  /* At this point we reached a fixed point and are done. */
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

LatticeValue & SCCPSolver::getLatticeValue( Value * const V )
{
  /* Get the LatticeValue for V.  If V was not already a key for the map, it
   * will immediately be inserted and mapped to BOTTOM.
   */
  auto it = ValueMap.insert( std::make_pair( V, LatticeValue() ) );
  LatticeValue &LV = it.first->second;

  /* For everything that is not supported, return TOP. */
  if ( ! V->getType()->isIntegerTy() )
  {
    LV.setTop();
    return LV;
  }

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
        LV.join( C );
  }

  return LV;
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

void SCCPSolver::visitBasicBlock( llvm::BasicBlock &BB )
{
  /* Add all instructions in this BB to the worklist */
  for ( auto Inst = BB.begin(); Inst != BB.end(); ++Inst )
    addToWorkList( Inst );
}

void SCCPSolver::visitBinaryOperator( llvm::BinaryOperator &I )
{
  LatticeValue &LV = getLatticeValue( &I );
  if ( LV.isTop() )
    return;

  LatticeValue &LVOp0 = getLatticeValue( I.getOperand( 0 ) );
  LatticeValue &LVOp1 = getLatticeValue( I.getOperand( 1 ) );

  /* If at least one of the LV is BOTTOM, we can't make any assumption, so stop.
   * here.
   */
  if ( LVOp0.isBottom() || LVOp1.isBottom() )
    return;

  /* If at least one of the operands is top, the result will be top. */
  if ( LVOp0.isTop() || LVOp1.isTop() )
  {
    LV.setTop();
    addToWorkList( &I );
  }

  /* Compute the new value for this LV.  If the LV changed, add it to the work
   * list.
   */
  if ( LV.join( ConstantExpr::get( I.getOpcode(),
          LVOp0.getConstant(), LVOp1.getConstant() ) ) )
  {
    addToWorkList( &I );
  }
}

void SCCPSolver::visitCallInst( llvm::CallInst &I )
{
  LatticeValue &LV = getLatticeValue( &I );
  if ( LV.isTop() )
    return;

  /* Always assume top */
  LV.setTop();
  addToWorkList( &I );
}

void SCCPSolver::visitCastInst( llvm::CastInst &I )
{
  LatticeValue &LV = getLatticeValue( &I );
  if ( LV.isTop() )
    return;

  LatticeValue &LVOp = getLatticeValue( I.getOperand( 0 ) );

  if ( LVOp.isBottom() )
    return;

  if ( LVOp.isTop() )
  {
    LV.setTop();
    return;
  }

  if ( LV.join( ConstantExpr::getCast(
          I.getOpcode(), LVOp.getConstant(), I.getType() ) ) )
    addToWorkList( &I );
}

void SCCPSolver::visitICmpInst( llvm::ICmpInst &I )
{
  LatticeValue &LV = getLatticeValue ( &I );

  if ( LV.isTop() )
    return;

  LatticeValue &LVOp0 = getLatticeValue( I.getOperand( 0 ) );
  LatticeValue &LVOp1 = getLatticeValue( I.getOperand( 1 ) );

  /* If at least one of the LV is BOTTOM, we can't make any assumption, so stop.
   * here.
   */
  if ( LVOp0.isBottom() || LVOp1.isBottom() )
    return;

  /* If at least one of the operands is top, the result will be top.
   * NOTE: We could make special cases for max-int and min-int values.
   */
  if ( LVOp0.isTop() || LVOp1.isTop() )
  {
    LV.setTop();
    addToWorkList( &I );
  }

  /* Compute the new value for this LV.  If the LV changed, add it to the work
   * list.
   */
  if ( LV.join( ConstantExpr::getCompare( I.getPredicate(),
          LVOp0.getConstant(), LVOp1.getConstant() ) ) )
    addToWorkList( &I );
}

void SCCPSolver::visitLoadInst( llvm::LoadInst &I )
{
  LatticeValue &LV = getLatticeValue( &I );
  if ( LV.isTop() )
    return;

  /* Always assume top */
  LV.setTop();
  addToWorkList( &I );
}

void SCCPSolver::visitStoreInst( llvm::StoreInst &I )
{
  LatticeValue &LV = getLatticeValue( &I );
  if ( LV.isTop() )
    return;

  /* Always assume top */
  LV.setTop();
  addToWorkList( &I );
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

void SCCPSolver::visitReturnInst( llvm::ReturnInst & )
{
  /* nothing to do here... */
}
