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


void IllegalExtDecl::emit( CodeGenFunction & ) const
{
  assert( false && "cannot emit code for illegal AST node" );
}

void Decl::emit( CodeGenFunction &CGF ) const
{
  assert( false && "not implemented yet" );
}

void StructDecl::emit( CodeGenFunction &CGF ) const
{
  assert( false && "not implemented yet" );
}

void ParamDecl::emit( CodeGenFunction &CGF ) const
{
  assert( false && "not implemented yet" );
}

void FunctionDef::emit( CodeGenFunction &CGF ) const
{
  assert( false && "not implemented yet" );
}
