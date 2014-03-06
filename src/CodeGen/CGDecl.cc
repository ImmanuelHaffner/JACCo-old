//===--- CGDecl.cc --------------------------------------------------------===//
//
//  ~~~ The C4 Compiler ~~~
//
//  This file implements the code generation for declarations.
//
//===----------------------------------------------------------------------===//


#include "CodeGen.h"

#include "../Support/Symbol.h"
#include "../AST/Decl.h"
#include "../AST/Stmt.h"
#include "../Support/Entity.h"
#include "../Support/EntityHolder.h"


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
  /* Get the entity. */
  Entity * const entity = this->getEntity();

  /* Create the LLVM type. */
  llvm::Type * type = entity->type->getLLVMType( CGF );

  /* If thisis just a type specifier, stop here. */
  if ( ! declarator ) return;

  /* If this is a function declaration, we only have to create a type.
   * Stop here.
   */
  if ( dynamic_cast< FuncType const * >( entity->type ) )
    return;

  /* Get the name of the identifier.  The declaration has an declarator,
   * and thus the parent of the attached entity bust be an identifier.
   */
  Identifier const * const id =
    static_cast< Identifier const * >( getEntity()->getParent() );

  if ( isGlobal )
  {
    /* Create a global variable. */
    entity->value = new GlobalVariable(
        CGF.M,                                  /* Module & */
        type,                                   /* Type * */
        false,                                  /* bool isConstant */
        GlobalValue::CommonLinkage,             /* LinkageType */
        Constant::getNullValue(type),           /* Constant * Initializer */
        id->tok.sym.str()                       /* const Twine &Name = "" */
        );
  }
  else
  {
    /* Create an alloca at the beginning of the current basic block. */
    entity->value = new AllocaInst(
        type,                                   /* Type */
        0,                                      /* Array Size = 0 */
        id->tok.sym.str(),                      /* Name */
        CGF.Builder.GetInsertBlock()->begin()   /* InsertBefore = 0 */
        );
  }
}

void FunctionDef::emit( CodeGenFunction &CGF, bool /* = false */ )
  const
{
  /* Get the LLVM type of the function. */
  FunctionType * type = static_cast< FunctionType * >(
      this->decl->getEntity()->type->getLLVMType( CGF ) );

  /* Get the name of the function. */
  Identifier const * const id =
    static_cast< Identifier const * >( this->decl->getEntity()->getParent() );

  /* Create the LLVM function. */
  Function *func = Function::Create(
      type,                         /* Function type */
      GlobalValue::ExternalLinkage, /* Linkage type */
      id->tok.sym.str(),            /* Function name */
      &(CGF.M)                      /* Module = 0 */
      );

  /* Add a first basic block to the function, that becomes the entry point for
   * the function.  This will automatically convert the function from a
   * declaration to a definition.
   */
  Twine name( id->tok.sym.str() );
  name.concat( ".entry" );
  BasicBlock *funcEntry = BasicBlock::Create(
      CGF.Context,  /* LLVM Context */
      name,         /* Name */
      func          /* Parent */
      );

  /* Set the insert point for the builder to the entry of the function. */
  CGF.Builder.SetInsertPoint( funcEntry );

  this->compStmt->emit( CGF );

  // Connect goto stmts with their labels.
  CGF.WireLabels();

  verifyFunction( *func );
}
