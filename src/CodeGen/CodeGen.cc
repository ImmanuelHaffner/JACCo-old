//===--- CodeGen.cc -------------------------------------------------------===//
//
//  ~~~ The C4 Compiler ~~~
//
//  This file implements the code gen function class and other more general
//  parts of the code gen.
//
//===----------------------------------------------------------------------===//


#include "CodeGen.h"

#include "../AST/AST.h"
#include "../Sema/TypeFactory.h"


using namespace C4;
using namespace AST;
using namespace Sema;
using namespace CodeGen;
using namespace llvm;


void TranslationUnit::emit( CodeGenFunction &CGF ) const
{
  /* Emit code for all external declarations. */
  for ( auto it = begin(); it != end(); ++it )
    (*it)->emit( CGF, /* isGlobal = */ true );
}

void CodeGenFunction::EmitBlock( BasicBlock * const target )
{
  if ( ! Builder.GetInsertPoint()->isTerminator() )
    Builder.CreateBr( target );
  Builder.SetInsertPoint( target );
}
