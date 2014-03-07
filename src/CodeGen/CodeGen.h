//===--- CodeGen.h --------------------------------------------------------===//
//
//  ~~~ The C4 Compiler ~~~
//
//  This file defines the interface for code generation.
//
//===----------------------------------------------------------------------===//


#ifndef C4_CODEGEN_H
#define C4_CODEGEN_H


#include <utility>
#include <vector>
#include "llvm/IR/Module.h"                /* Module */
#include "llvm/IR/Function.h"              /* Function */
#include "llvm/IR/Constant.h"              /* Constant::getNullValue */
#include "llvm/IR/IRBuilder.h"             /* IRBuilder */
#include "llvm/IR/LLVMContext.h"           /* LLVMContext */
#include "llvm/IR/GlobalValue.h"           /* GlobaleVariable, LinkageTypes */
#include "llvm/Analysis/Verifier.h"        /* verifyFunction, verifyModule */
#include "llvm/Support/Host.h"
#include "../Support/Symbol.h"
#include "../Sema/Type.h"


namespace C4
{
  namespace CodeGen
  {
    /// \brief Stores the break and continue targets for a loop.
    struct JumpTarget
    {
      JumpTarget( llvm::BasicBlock * const breakTarget,
          llvm::BasicBlock * const continueTarget )
        : breakTarget(breakTarget), continueTarget(continueTarget)
      {}

      ~JumpTarget() {}

      llvm::BasicBlock * const breakTarget;
      llvm::BasicBlock * const continueTarget;
    };

    /// \brief Holds the most important objects for code generation and offers
    /// routines for common code gen tasks.
    struct CodeGenFunction
    {
      CodeGenFunction( char const * const fileName )
        : Context( llvm::getGlobalContext() ), M( fileName, Context ),
        Builder( llvm::getGlobalContext() )
      { M.setTargetTriple(llvm::sys::getDefaultTargetTriple()); }

      ~CodeGenFunction() {}

      inline void pushJumpTarget( JumpTarget const target )
      {
        jumpTargets.push_back( target );
      }

      inline JumpTarget getCurrentJumpTarget() const
      {
        return jumpTargets.back();
      }

      inline JumpTarget popJumpTarget()
      {
        JumpTarget const t = jumpTargets.back();
        jumpTargets.pop_back();
        return t;
      }

      inline void addGoto( Symbol sym, llvm::BasicBlock * const basicBlock )
      {
        gotoTargets.push_back( std::make_pair( sym, basicBlock ) );
      }

      inline void addLabel( Symbol sym, llvm::BasicBlock * const basicBlock )
      {
        labels.insert( std::make_pair( sym, basicBlock ) );
      }


      //===---------------------------------------------------------------------
      //
      //  CodeGen Helper Functions
      //
      //===---------------------------------------------------------------------

      /// If the current block is not terminated already, creates a branch from
      /// it to the target block.  Sets the insert point of the builder to the
      /// target block.
      void EmitBlock( llvm::BasicBlock * const target );

      /// \return a new BasicBlock of given name, with the current function as
      /// parent
      llvm::BasicBlock * getBasicBlock( llvm::Twine const &Name = "" );

      /// Creates branches between goto-stmts and their associated labels.
      /// Must be called after completing a function definition.
      void WireLabels();

      /// Evaluates the given expression to a bool (i1) value.
      /// A pointer expression will be compared to NULL, an integer expression
      /// will be compared to 0 (zero).
      ///
      /// \return the bool value of the expression
      llvm::Value * EvaluateExprAsBool( llvm::Value *expr );

      llvm::Value * GetAs( llvm::Value *val, llvm::Type *type );


      /* The global context (only one needed) */
      llvm::LLVMContext &Context;

      /* A Module (only one needed) */
      llvm::Module M;

      /* An IR-Builder to output intermediate instructions or types. */
      llvm::IRBuilder<> Builder;

      /* Points to the current function.
       * May be NULL.
       */
      llvm::Function *parent = NULL;

      /* A stack of all parameter allocas in the order they have been created.
       * Must be cleared after each function definition.
       */
      std::vector< llvm::Value * > params;

      private:
      /* A stack of the break/continue targets for loops. */
      std::vector< JumpTarget > jumpTargets;

      /* A map of labels and corresponding basic blocks. */
      std::unordered_map< Symbol, llvm::BasicBlock * const > labels;

      /* A stack of pairs of goto targets and corresponding insert points. */
      std::vector< std::pair< Symbol, llvm::BasicBlock * const > > gotoTargets;
    };
  } // end namespace CodeGen
} // end namespace C4


#endif
