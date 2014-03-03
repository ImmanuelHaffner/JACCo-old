//===--- CGDecl.cc --------------------------------------------------------===//
//
//  ~~~ The C4 Compiler ~~~
//
//  This file implements the code generation for declarations.
//
//===----------------------------------------------------------------------===//


#include "../AST/Decl.h"


using namespace C4;
using namespace AST;
using namespace Sema;
using namespace CodeGen;


void ExtDecl::emit( CodeGenFunction & ) const
{
  assert( false && "not implemented yet" );
}
