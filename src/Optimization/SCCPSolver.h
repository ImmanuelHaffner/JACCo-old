#ifndef SCCPVISITOR_H
#define SCCPVISITOR_H


#include "llvm/InstVisitor.h"
#include "llvm/ADT/DenseMap.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/SmallPtrSet.h"
#include "LatticeValue.h"


namespace C4
{
  namespace Optimize
  {
    typedef llvm::DenseMap< llvm::Value *, LatticeValue > ValueMap_t;

    struct SCCPSolver : llvm::InstVisitor< SCCPSolver >
    {
      SCCPSolver() {}

      /// Apply SCCP to the given function.
      ///
      /// \param F the function SCCP shall be applied to
      void solve( llvm::Function *F );


      private:
      friend class llvm::InstVisitor< SCCPSolver >;

      /// Marks the given value as TOP.
      ///
      /// \param V the value to mark as TOP
      void markTop( llvm::Value *V );

      /// Returns the lattice value of the corresponding value. Inserts it
      /// into the ValueMap if not already there.
      ///
      /// \param V the value for which we want to get the lattice value
      /// \returns the lattice value of V
      LatticeValue & getLatticeValue( llvm::Value *V );

      /// Inserts the given BasicBlock in the set of all reachable BasicBlocks.
      void markBlockVisitable ( llvm::BasicBlock * );


      //===----------------------------------------------------------------===//
      //
      //  Visit Methods
      //
      //  The visit methods implement the transfer function for the LLVM
      //  instructions and basiv blocks.  If the LatticeValue of an instruction
      //  changed, adds the instruction or basic block to a work list.
      //
      //===----------------------------------------------------------------===//

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
      ValueMap_t ValueMap;
    };
  }
}


#endif
