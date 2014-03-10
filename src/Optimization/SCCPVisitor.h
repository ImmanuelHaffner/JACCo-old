#ifndef SCCPVISITOR_H
#define SCCPVISITOR_H

#include <llvm/InstVisitor.h>

namespace C4
{
  namespace Optimize
  {
    struct SCCPVisitor : llvm::InstVisitor< SCCPVisitor >
    {
      SCCPVisitor() {}

      SmallVector< BasicBlock *, 64 >  BBWorklist;
      SmallVector< Value *, 64 > InstrTopWorklist;
      SmallVector< Value *, 64 > InstrWorklist;

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
    };
  }
}
#endif
