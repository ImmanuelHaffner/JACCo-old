#include "Optimization.h"

using namespace C4;
using namespace Optimize;
using namespace llvm;


void Optimizer::runMem2Reg( Module * const module )
{
  llvm::PassManager pm;
  pm.add( llvm::createPromoteMemoryToRegisterPass() );
  pm.run( *module );
}


void Optimizer::optimize( Module * const module )
{
  runMem2Reg( module );
}
