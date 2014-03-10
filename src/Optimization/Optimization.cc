#include "Optimization.h"
#include "SCCPVisitor.h"

using namespace C4;
using namespace Optimize;
using namespace llvm;


void Optimizer::runMem2Reg( Module &module )
{
  llvm::PassManager pm;
  pm.add( llvm::createPromoteMemoryToRegisterPass() );
  pm.run( module );
}


void Optimizer::optimize( Module &module )
{
  runMem2Reg( module );
  SCCPVisitor sccpVisitor;
}
