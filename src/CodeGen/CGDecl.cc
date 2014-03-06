//===--- CGDecl.cc --------------------------------------------------------===//
//
//  ~~~ The C4 Compiler ~~~
//
//  This file implements the code generation for declarations.
//
//===----------------------------------------------------------------------===//


#include "CodeGen.h"

#include "../AST/Decl.h"


using namespace C4;
using namespace AST;
using namespace Sema;
using namespace CodeGen;
using namespace llvm;


void IllegalExtDecl::emit( CodeGenFunction &, bool ) const
{
  assert( false && "cannot emit code for illegal AST node" );
}

void IllegalDecl::emit( CodeGenFunction &, bool ) const
{
  assert( false && "cannot emit code for illegal AST node" );
}

void Decl::emit( CodeGenFunction &CGF, bool isGlobal /* = false */ ) const
{
  assert( false && "not implemented yet" );
}

void StructDecl::emit( CodeGenFunction &CGF, bool isGlobal /* = false */ ) const
{
  assert( false && "not implemented yet" );
}

void ParamDecl::emit( CodeGenFunction &CGF, bool isGlobal /* = false */ ) const
{
  assert( false && "not implemented yet" );
}

void FunctionDef::emit( CodeGenFunction &CGF, bool isGlobal /* = false */ )
  const
{
  assert( false && "not implemented yet" );
}
