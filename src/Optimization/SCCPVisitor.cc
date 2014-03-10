#include "SCCPVisitor.h"

using namespace C4;
using namespace llvm;
using namespace Optimize;

void SCCPVisitor::runOnFunction( Function *F )
{
  /* Add first basic block to worklist */
  markBlockVisitable( F->begin() );

  /* Consider arguments as top */
  for (Function::arg_iterator AI = F->arg_begin(), E = F->arg_end();
      AI != E; ++AI)
    markTop(AI);
}

void SCCPVisitor::markTop( llvm::Value *V )
{
  ValueMap[ V ].setTop();
}

void SCCPVisitor::markBlockVisitable ( llvm::BasicBlock *BB )
{
  BBExecutable.insert( BB );
}

void SCCPVisitor::visitBinaryOperator( llvm::BinaryOperator &I )
{
  /* TODO: Implement */
  assert( false && "not implemented yet" );
}

void SCCPVisitor::visitCallInst( llvm::CallInst &I )
{
  /* TODO: Implement */
  assert( false && "not implemented yet" );
}
void SCCPVisitor::visitCastInst( llvm::CastInst &I )
{
  /* TODO: Implement */
  assert( false && "not implemented yet" );
}
void SCCPVisitor::visitICmpInst( llvm::ICmpInst &I )
{
  /* TODO: Implement */
  assert( false && "not implemented yet" );
}
void SCCPVisitor::visitLoadInst( llvm::LoadInst &I )
{
  /* TODO: Implement */
  assert( false && "not implemented yet" );
}
void SCCPVisitor::visitStoreInst( llvm::StoreInst &I )
{
  /* TODO: Implement */
  assert( false && "not implemented yet" );
}
void SCCPVisitor::visitPHINode( llvm::PHINode &I )
{
  /* TODO: Implement */
  assert( false && "not implemented yet" );
}
void SCCPVisitor::visitBranchInst( llvm::BranchInst &I )
{
  /* TODO: Implement */
  assert( false && "not implemented yet" );
}
void SCCPVisitor::visitReturnInst( llvm::ReturnInst &I )
{
  /* TODO: Implement */
  assert( false && "not implemented yet" );
}
