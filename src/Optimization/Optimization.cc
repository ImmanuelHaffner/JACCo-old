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


void Optimizer::optimize( Module &M )
{
  runMem2Reg( M );

  SCCPVisitor sccpVisitor;
  for ( Module::iterator F = M.begin(); F != M.end(); ++F )
  {
    /* Check whether we have a definition */
    if ( ! F->isDeclaration() )
    {
      sccpVisitor.runOnFunction( F );
    }
  }

  runMem2Reg( M );
}
