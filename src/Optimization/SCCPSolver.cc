#include "SCCPSolver.h"

#include "llvm/IR/Value.h"
#include "llvm/IR/Constants.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"


using namespace C4;
using namespace llvm;
using namespace Optimize;


/// Removes all instructions from this basic block except for the terminator.
static void ClearBlock( BasicBlock * const BB )
{
  if ( isa< TerminatorInst >( BB->begin() ) )
    return;

  Instruction *T = BB->getTerminator();
  assert( T && "every basic block must have a terminator" );

  /* Keep removing the immediate predecessor instruction of the terminator,
   * until the terminator is the last remaining instruction.
   */
  while ( T != BB->begin() )
  {
    BasicBlock::iterator I = T;
    Instruction *Inst = --I;

    if ( ! Inst->use_empty() )
      Inst->replaceAllUsesWith( UndefValue::get( Inst->getType() ) );

    BB->getInstList().erase( Inst );
  }
}

LatticeValue SCCPSolver::runOnFunction( Function &F,
    SmallVector< LatticeValue, 2 > *Args /* = NULL */ )
{
  Module * const M = F.getParent();
  assert( M && "every function needs a module" );

  SCCPSolver Solver;

  /* Add first basic block to worklist. */
  Solver.addToWorkList( F.begin() );

  /* Initialize all arguments. */
  if ( NULL == Args )
    for ( Function::arg_iterator AI = F.arg_begin(); AI != F.arg_end(); ++AI )
      Solver.ValueMap[ AI ].setTop();
  else
  {
    assert( F.getArgumentList().size() == Args->size() &&
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
  SmallVector< Instruction *, 64 > ToReplace;
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
      LatticeValue &LV = Solver.getLatticeValue( Inst );
      if ( LV.isTop() )
        continue;

      ToReplace.push_back( Inst );
    }

    /*TerminatorInst *TI = BB->getTerminator();
    for ( unsigned i = 0, e = TI->getNumSuccessors(); i != e; ++i ) {
      BasicBlock *Succ = TI->getSuccessor( i );
      if ( ! Succ->empty() && isa< PHINode >( Succ->begin() ) )
        TI->getSuccessor( i )->removePredecessor( BB );
    }

    if ( ! TI->use_empty() )
      TI->replaceAllUsesWith( UndefValue::get( TI->getType() ) );
    
    TI->eraseFromParent();*/
  }

  /* Clear unreachable basic blocks. */
  while ( ! BBsToEmpty.empty() )
    ClearBlock( BBsToEmpty.pop_back_val() );

  /* Replace instructions by constants. */
  while ( ! ToReplace.empty() )
  {
    Instruction *Inst = ToReplace.pop_back_val();
    LatticeValue &LV = Solver.getLatticeValue( Inst );

    /* Skip calls with LV BOTTOM. */
    if ( ! LV.isConstant() && isa< CallInst >( Inst ) )
      continue;

    Constant *Const = LV.isConstant() ?
      LV.getConstant() : UndefValue::get( Inst->getType() );

    /* Replace all uses of the instruction. */
    Inst->replaceAllUsesWith( Const );

    /* Remove the instruction. */
    Inst->eraseFromParent();
  }

  /* Compute the LV for the return of the funtion. */
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
    if ( ! InstrTopWorklist.empty() )
      do
        notifyUses( InstrTopWorklist.pop_back_val() );
      while ( ! InstrTopWorklist.empty() );
    else if ( ! InstrWorklist.empty() )
      notifyUses( InstrWorklist.pop_back_val() );
    else if ( ! BBWorklist.empty() )
      /* Notify all instructions in this basic block that they are newly
       * executable.
       */
      visit( BBWorklist.pop_back_val() );
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
  if ( BBExecutable.insert( BB ) )
    BBWorklist.push_back( BB );
  else
  {
    /* If the basic block was already reachable, update incoming edges of
     * all successing phi nodes.
     */
    for ( BasicBlock::iterator I = BB->begin(); ; ++I )
      if ( PHINode * const Phi = dyn_cast< PHINode >( I ) )
        visitPHINode( *Phi );
      else
        /* PHINodes must be in the beginning of a basic block. */
        break;
  }
}


//===----------------------------------------------------------------------===//
//
//  Visit Methods
//
//===----------------------------------------------------------------------===//

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
    return;
  }

  /* Compute the new value for this LV.  If the LV changed, add it to the work
   * list.
   */
  if ( LV.join( ConstantExpr::get( I.getOpcode(),
          LVOp0.getConstant(), LVOp1.getConstant() ) ) )
    addToWorkList( &I );
}

void SCCPSolver::visitCallInst( llvm::CallInst &I )
{
  LatticeValue &LV = getLatticeValue( &I );
  if ( LV.isTop() )
    return;

  /* For now, just always assume TOP.
   * TODO Remove for inter-procedural SCCP.
   */
  LV.setTop();
  return;

  Function *F = I.getCalledFunction();

  /* If the function is not a definition, skip it. */
  if ( F->isDeclaration() )
    return;

  /* Collect the arguments for the function call. */
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
    if ( ! BBExecutable.count( *itBB ) )
      continue;

    /* Check if incoming edge comes from a conditional branch */
    if ( BranchInst * const BI =
      dyn_cast< BranchInst >( ( *itBB )->getTerminator() ) )
    {
      if ( BI->isConditional() )
      {
        /* If the LV of the condition is BOTTOM, assume the branch is not taken
         * and skip.
         */
        LatticeValue &LVCond = getLatticeValue( BI->getCondition() );
        if ( LVCond.isBottom() )
          continue;

        /* Check whether the conditional branch never takes the edge to the
         * current basic block.  If so, skip it.
         */
        if ( LVCond.isConstant() &&
            BI->getSuccessor( LVCond.getConstant()->isZeroValue() ) !=
            I.getParent() )
          continue;
      }
    }

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

  /* If the LV of the condition is BOTTOM, we assume the branch is never being
   * evaluated.
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
