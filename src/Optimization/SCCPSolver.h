#ifndef SCCPVISITOR_H
#define SCCPVISITOR_H


#include <vector>
#include "llvm/IR/Module.h"                 /* Module */
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

      static LatticeValue runOnFunction( llvm::Function &F,
          llvm::SmallVector< LatticeValue, 2 > *Args = NULL );

      /// Finad a fixed point for SCCP and the given function.
      ///
      /// \param F the function a SCCP fixed point should be computed for
      void solve();

      private:
      friend class llvm::InstVisitor< SCCPSolver >;


      //===----------------------------------------------------------------===//
      //
      //  Helper Methods
      //
      //  These methods provide some routines for SCCP.
      //
      //===----------------------------------------------------------------===//

      /// Returns the lattice value of the corresponding value. Inserts it
      /// into the ValueMap if not already there.
      ///
      /// \param V the value for which we want to get the lattice value
      /// \returns the lattice value of V
      LatticeValue & getLatticeValue( llvm::Value *V );

      /// Notifies all uses of V the value, that it's LatticeValue has changed.
      ///
      /// \param V the Value whos uses you want to notify
      void notifyUses( llvm::Value * const V );

      void addToWorkList( llvm::Value * const V );

      void addToWorkList( llvm::BasicBlock * const BB );


      //===----------------------------------------------------------------===//
      //
      //  Visit Methods
      //
      //  The visit methods implement the transfer function for the LLVM
      //  instructions and basic blocks.  If the LatticeValue of an instruction
      //  changed, adds the instruction or basic block to a work list.
      //
      //===----------------------------------------------------------------===//

      virtual void visitBinaryOperator( llvm::BinaryOperator &I );
      virtual void visitCallInst( llvm::CallInst &I );
      virtual void visitCastInst( llvm::CastInst &I );
      virtual void visitICmpInst( llvm::ICmpInst &I );
      virtual void visitLoadInst( llvm::LoadInst &I );
      virtual void visitStoreInst( llvm::StoreInst &I );
      virtual void visitPHINode( llvm::PHINode &I );
      virtual void visitBranchInst( llvm::BranchInst &I );
      virtual void visitReturnInst( llvm::ReturnInst &I );

      llvm::SmallVector< llvm::BasicBlock *, 64 >  BBWorklist;
      llvm::SmallVector< llvm::Value *, 64 > InstrTopWorklist;
      llvm::SmallVector< llvm::Value *, 64 > InstrWorklist;
      llvm::SmallPtrSet< llvm::BasicBlock *, 8 > BBExecutable;
      llvm::SmallPtrSet< LatticeValue *, 2 > ReturnValues;
      ValueMap_t ValueMap;
    };
  }
}


#endif
