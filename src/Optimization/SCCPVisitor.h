#ifndef SCCPVISITOR_H
#define SCCPVISITOR_H

#include <llvm/InstVisitor.h>
#include <llvm/ADT/DenseMap.h>
#include <llvm/ADT/SmallVector.h>
#include <llvm/ADT/SmallPtrSet.h>
#include "LatticeValue.h"

namespace C4
{
  namespace Optimize
  {
    typedef llvm::DenseMap< llvm::Value *, LatticeValue > ValueMap;

    struct SCCPVisitor : llvm::InstVisitor< SCCPVisitor >
    {
      SCCPVisitor() {}

      void runOnFunction( llvm::Function *F );
      void markTop( llvm::Value * );
      void markBlockVisitable ( llvm::BasicBlock * );

      private:
      friend class llvm::InstVisitor< SCCPVisitor >;

      void visitBinaryOperator( llvm::BinaryOperator &I );
      void visitCallInst( llvm::CallInst &I );
      void visitCastInst( llvm::CastInst &I );
      void visitICmpInst( llvm::ICmpInst &I );
      void visitLoadInst( llvm::LoadInst &I );
      void visitStoreInst( llvm::StoreInst &I );
      void visitPHINode( llvm::PHINode &I );
      void visitBranchInst( llvm::BranchInst &I );
      void visitReturnInst( llvm::ReturnInst &I );

      llvm::SmallVector< llvm::BasicBlock *, 64 >  BBWorklist;
      llvm::SmallVector< llvm::Value *, 64 > InstrTopWorklist;
      llvm::SmallVector< llvm::Value *, 64 > InstrWorklist;
      llvm::SmallPtrSet< llvm::BasicBlock *, 8 > BBExecutable;
      ValueMap ValueMap;
    };
  }
}
#endif
