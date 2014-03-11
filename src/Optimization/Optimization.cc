#include "Optimization.h"
#include "SCCPSolver.h"

using namespace C4;
using namespace Optimize;
using namespace llvm;


void Optimizer::runMem2Reg( Module &M )
{
  llvm::PassManager pm;
  pm.add( llvm::createPromoteMemoryToRegisterPass() );
  pm.run( M );
}


void Optimizer::runSCCP( Module &M )
{
  for ( auto funcIt = M.begin(); funcIt != M.end(); ++funcIt )
  {
    /* Skip declarations. */
    if ( funcIt->isDeclaration() )
      continue;

    SCCPSolver::runOnFunction( *funcIt );
  }
}
