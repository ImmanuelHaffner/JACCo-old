#include "Optimization.h"
#include "SCCPSolver.h"

using namespace C4;
using namespace Optimize;
using namespace llvm;


void Optimizer::runMem2Reg( Module &module )
{
  llvm::PassManager pm;
  pm.add( llvm::createPromoteMemoryToRegisterPass() );
  pm.run( module );
}


void Optimizer::runSCCP( Module &M )
{
  SCCPSolver SCCPSolver;
  for ( Module::iterator F = M.begin(); F != M.end(); ++F )
  {
    /* Check whether we have a definition */
    if ( ! F->isDeclaration() )
    {
      SCCPSolver.solve( F );
    }
  }
}
