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
    /* Get the current basic block. */
    BasicBlock * curBB = CGF.Builder.GetInsertBlock();

    /* Create an alloca at the beginning of the current basic block. */
    if ( curBB->empty() )
    {
      getEntity()->value = CGF.Builder.CreateAlloca(
          type,             /* Type */
          0,                /* ArraySize = 0 */
          id->tok.sym.str() /* Name */
          );
    }
    else
    {
      /* Create the alloca instruction. */
      Instruction * alloca = new AllocaInst(
          type,             /* Type */
          0,                /* Array Size = 0 */
          id->tok.sym.str() /* Name */
          );

      alloca->insertBefore( curBB->begin() );
      getEntity()->value = alloca;
    }
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

  /* Set the current function in the CGF. */
  CGF.parent = func;

  /* Add a first basic block to the function, that becomes the entry point for
   * the function.  This will automatically convert the function from a
   * declaration to a definition.
   */
  Twine name( id->tok.sym.str() );
  name.concat( ".entry" );
  BasicBlock *funcEntry = CGF.getBasicBlock( name );

  /* Set the insert point for the builder to the entry of the function. */
  CGF.Builder.SetInsertPoint( funcEntry );

  this->compStmt->emit( CGF );

  /* If there was no return (allowed if the return type is void), then emit a
   * return here.
   */
  if ( ! CGF.Builder.GetInsertPoint()->isTerminator() )
    CGF.Builder.CreateRetVoid();

  // Connect goto stmts with their labels.
  CGF.WireLabels();

  /* Remove the function as current parent from CGF. */
  CGF.parent = NULL;

  verifyFunction( *func );
}
