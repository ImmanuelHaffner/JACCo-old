#include "SCCPSolver.h"

#include "llvm/IR/Value.h"
#include "llvm/IR/Constants.h"


using namespace C4;
using namespace llvm;
using namespace Optimize;


/// Removes all instructions from this basic block except for the terminator.
static void ClearBlock( BasicBlock * const BB )
{
  if ( BB->begin()->isTerminator() )
    return;

  SmallVector< Instruction *, 8 > ToRemove;

  BasicBlock::iterator I = BB->getTerminator();
  while ( I != BB->begin() )
  {
    Instruction *Inst = --I;
    ToRemove.push_back( Inst );
  }

  while ( ! ToRemove.empty() )
    BB->getInstList().erase( ToRemove.pop_back_val() );
}

LatticeValue SCCPSolver::runOnFunction( Function &F,
    SmallVector< LatticeValue, 2 > *Args /* = NULL */ )
{
  SCCPSolver Solver;

  /* Add first basic block to worklist. */
  Solver.addToWorkList( F.begin() );

  /* Initialize all arguments. */
  if ( NULL == Args )
    for ( Function::arg_iterator AI = F.arg_begin(); AI != F.arg_end(); ++AI )
      Solver.ValueMap[ AI ].setTop();
  else
  {
    assert( F.getNumOperands() == Args->size() &&
        "incorrect amount of arguments" );

    auto LV = Args->begin();
    for ( Function::arg_iterator AI = F.arg_begin(); AI != F.arg_end();
        ++AI, ++LV )
      Solver.ValueMap[ AI ] = *LV;
  }

  Solver.solve();

  /* Vectors to collect the things to remove or replace.  We need this, since
   * iterators would be invalidated when removing instructions while iterating
   * through their basic blocks.
   */
  SmallVector< Instruction *, 64 > InstsToRemove;
  SmallVector< CallInst *, 64 > CallInsts;
  SmallVector< BranchInst *, 64 > BranchInstToReplace;
  SmallVector< BasicBlock *, 8 > BBsToEmpty;

  /* Now that we have solved SCCP, remove unreachable blocks and replace
   * instructions with their constants.
   * First, collect all unreachable BBs and all replacable instructions.
   */
  for ( auto BB = F.begin(); BB != F.end(); ++BB )
  {
    /* If the BB is unreachable, add it to the stack of BBs to clear. */
    if ( ! Solver.BBExecutable.count( BB ) )
    {
      BBsToEmpty.push_back( BB );
      continue;
    }

    /* Iterate over all instructions of the BB. */
    for ( auto Inst = BB->begin(); Inst != BB->end(); ++Inst )
    {
      if ( isa< TerminatorInst >( Inst ) )
        continue;

      LatticeValue &LV = Solver.getLatticeValue( Inst );

      /* Check whether we can replace a conditional branch with an unconditional
       * branch.
       */
      if ( auto *BInst = dyn_cast< BranchInst >( Inst ) )
      {
        /* Skip unconditional branches. */
        if ( BInst->isUnconditional() )
          continue;

        LatticeValue &LVCond = Solver.getLatticeValue( BInst->getCondition() );
        if ( LVCond.isTop() )
          continue;

        BranchInstToReplace.push_back( BInst );
      }
      else if ( auto *Call = dyn_cast< CallInst >( Inst ) )
      {
        if ( LV.isTop() )
          continue;

        CallInsts.push_back( Call );
      }
      else
      {
        if ( LV.isTop() )
          continue;

        InstsToRemove.push_back( Inst );
      }
    }
  }

  /* Clear unreachable basic blocks. */
  while ( ! BBsToEmpty.empty() )
    ClearBlock( BBsToEmpty.pop_back_val() );

  /* Replace conditional branches by unconditional branches. */
  while ( ! BranchInstToReplace.empty() )
  {
    BranchInst *BInst = BranchInstToReplace.pop_back_val();
    LatticeValue &LVCond = Solver.getLatticeValue( BInst->getCondition() );

    /* Create an unconditional branch. */
    auto BInstNew = BranchInst::Create(
        BInst->getSuccessor( LVCond.getConstant()->isZeroValue() ) );

    /* Replace all uses of the conditional branch by the unconditional
     * branch. */
    BInst->replaceAllUsesWith( BInstNew );

    /* Remove the conditional branch instruction. */
    BInst->eraseFromParent();
  }

  /* Replace instructions by constants. */
  while ( ! InstsToRemove.empty() )
  {
    Instruction *Inst = InstsToRemove.pop_back_val();
    LatticeValue &LV = Solver.getLatticeValue( Inst );

    Constant *Const = LV.isConstant() ?
      LV.getConstant() : UndefValue::get( Inst->getType() );

    /* Replace all uses of the instruction. */
    Inst->replaceAllUsesWith( Const );

    /* Remove the instruction. */
    Inst->eraseFromParent();
  }

  /* Replace CallInsts if possible. */
  while ( ! CallInsts.empty() )
  {
    CallInst *Call = CallInsts.pop_back_val();
    LatticeValue &LV = Solver.getLatticeValue( Call );

    if ( ! LV.isConstant() )
      continue;

    Call->replaceAllUsesWith( LV.getConstant() );
    Call->eraseFromParent();
  }

  /* Clear unreachable basic blocks. */
  while ( ! BBsToEmpty.empty() )
    ClearBlock( BBsToEmpty.pop_back_val() );

  LatticeValue RV;
  for ( auto I = Solver.ReturnValues.begin(); I != Solver.ReturnValues.end();
      ++I )
    RV.join( **I );

  return RV;
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

  Function *F = I.getCalledFunction();
  if ( F->isDeclaration() )
    return;

  SmallVector< LatticeValue, 2 > Args;
  for ( unsigned i = 0; i < I.getNumArgOperands(); ++i )
    Args.push_back( getLatticeValue( I.getArgOperand( i ) ) );

  if ( LV.join( SCCPSolver::runOnFunction( *I.getCalledFunction(), &Args ) ) )
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
    return;
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

void SCCPSolver::visitReturnInst( llvm::ReturnInst &I )
{
  ReturnValues.insert( & getLatticeValue( &I ) );
}
