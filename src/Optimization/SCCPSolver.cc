#include "SCCPSolver.h"

#include "llvm/Value.h"


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
    if ( ! InstrTopWorklist.empty() )
    {
      Value *I = InstrTopWorklist.pop_back_val();

      for ( auto U = I->use_begin(); U != I->use_end(); ++U )
        if ( Instruction *UI = dyn_cast< Instruction >( U )
            /* OperandChangeState( UI ) */;
    }
    else if ( ! InstrWorklist.empty() )
    {
      Value *I = InstrWorklist.pop_back_val();

      for ( auto U = I->use_begin(); U != I->use_end(); ++U )
        if ( Instruction *UI = dyn_cast< Instruction >( U )
            /* OperandChangeState( UI ) */;
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

void SCCPSolver::visitBinaryOperator( llvm::BinaryOperator &I )
{
  /* TODO: Implement */
  assert( false && "not implemented yet" );
}

void SCCPSolver::visitCallInst( llvm::CallInst &I )
{
  /* TODO: Implement */
  assert( false && "not implemented yet" );
}
void SCCPSolver::visitCastInst( llvm::CastInst &I )
{
  /* TODO: Implement */
  assert( false && "not implemented yet" );
}
void SCCPSolver::visitICmpInst( llvm::ICmpInst &I )
{
  /* TODO: Implement */
  assert( false && "not implemented yet" );
}
void SCCPSolver::visitLoadInst( llvm::LoadInst &I )
{
  /* TODO: Implement */
  assert( false && "not implemented yet" );
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
