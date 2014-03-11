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

LatticeValue & SCCPSolver::getLatticeValue( Value *V )
{
  assert ( V->getType()->isIntegerTy() && "only track values of integer type" );
  /* Insert V into the Value map if not there;
   * if it already exists, get its position */
  std::pair< ValueMap::iterator, bool > it =
    ValueMap.insert( std::make_pair( V, LatticeValue() ) );
  LatticeValue &lv = it.first->second;

  if ( it.second )
  {
    /* Value wasn't in the map before */
    if ( Constant *C = dyn_cast< Constant >( V ) )
      if ( ! isa< UndefValue >( C ) )
        /* Mark it as constant */
        lv.setConstant( C );
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
  /* TODO: Implement */
  assert( false && "not implemented yet" );
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
  /* TODO: Implement */
  assert( false && "not implemented yet" );
  if ( getLatticeValue( &I ).isTop() )
    return;

  /* Iterate over incoming edges and try to infer a common constant */
  Constant *C = NULL;
  for ( unsigned i = 0; i < I.getNumIncomingValues(); ++i )
  {
    LatticeValue lv = getLatticeValue( I.getIncomingValue( i ) );

    if ( lv.isBottom() )
      /* Skip as it doesn't affect the result */
      continue;

    /* TODO: Check if edge is feasible */

    if ( lv.isTop() )
      /* PHINode will be top as well */
      return markTop( &I );

    /* We have a constant */
    if ( C == NULL )
      /* First constant we see, use it */
      C = lv.getConstant();

    if ( C != lv.getConstant() )
      /* Constants on at least two edges aren't the same, so we go to top */
      return markTop( &I );
  }

  /* PHINode is either constant or still undefined */
  if ( C )
    getLatticeValue( &I ).setConstant( C );

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
