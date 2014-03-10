//===--- Optimization.h ---------------------------------------------------------===//
//
//  ~~~ The C4 Compiler ~~~
//
//  This file defines the Parser interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_OPTIMIZATION_H
#define C4_OPTIMIZATION_H

#include <iostream>
#include <sstream>
#include <cstring>
#include "../util.h"
#include "../diagnostic.h"
#include "llvm/PassManager.h"
#include "llvm/Transforms/Scalar.h"


namespace C4
{
  namespace Optimize 
  {
    /// \brief The optimizer 
    struct Optimizer 
    {
      static void runMem2Reg( llvm::Module * const );
      static void optimize( llvm::Module * const );
    };
  }
}

#endif
