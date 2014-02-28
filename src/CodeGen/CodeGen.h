//===--- CodeGen.h --------------------------------------------------------===//
//
//  ~~~ The C4 Compiler ~~~
//
//  This file defines the interface for code generation.
//
//===----------------------------------------------------------------------===//

#ifndef C4_CODEGEN_H
#define C4_CODEGEN_H


#include "llvm/IR/Module.h"                /* Module */
#include "llvm/IR/Function.h"              /* Function */
#include "llvm/IR/Constant.h"              /* Constant::getNullValue */
#include "llvm/IR/IRBuilder.h"             /* IRBuilder */
#include "llvm/IR/LLVMContext.h"           /* LLVMContext */
#include "llvm/IR/GlobalValue.h"           /* GlobaleVariable, LinkageTypes */
#include "llvm/Analysis/Verifier.h"        /* verifyFunction, verifyModule */


using namespace llvm;


namespace C4
{
  namespace CodeGen
  {
    /// \brief Holds the most important objects for code generation and offers
    /// routines for common code gen tasks.
    struct CodeGenFunction
    {
      CodeGenFunction( char const * const fileName )
        : Context( getGlobalContext() ), M( fileName, Context )
      {}

      ~CodeGenFunction() {}

      private:
      /* The global context (only one needed) */
      LLVMContext &Context;

      /* A Module (only one needed) */
      Module M;
    };
  } // end namespace CodeGen
} // end namespace C4

#endif
