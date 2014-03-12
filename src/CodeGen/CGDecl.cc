//===--- CGDecl.cc --------------------------------------------------------===//
//
//  ~~~ The C4 Compiler ~~~
//
//  This file implements the code generation for declarations.
//
//===----------------------------------------------------------------------===//


#include "CodeGen.h"

#include <cstring>
#include "../Support/Symbol.h"
#include "../AST/Decl.h"
#include "../AST/Stmt.h"
#include "../Sema/TypeFactory.h"
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

  /* If this is just a type specifier, stop here. */
  if ( ! declarator ) return;

  /* Get the name of the identifier.  The declaration has an declarator,
   * and thus the parent of the attached entity must be an identifier.
   */
  Identifier const * const id =
    static_cast< Identifier const * >( getEntity()->getParent() );

  /* If this is a function declaration, we only have to create a type.
   * Stop here.
   * We use isGlobal as a dirty hack to avoid emitting code for declarations but
   * for definitions.
   */
  if ( dynamic_cast< FuncType const * >( entity->type ) )
  {
    Function *func = CGF.M.getFunction( id->tok.sym.str() );

    /* Create a function in the Module if it does not yet exist. */
    if ( ! func )
    {
      /* Get the LLVM type of the function. */
      FunctionType *funcType = static_cast< FunctionType * >( type );

      /* Create the LLVM function. */
      func = Function::Create(
          funcType,                     /* Function type */
          GlobalValue::ExternalLinkage, /* Linkage type */
          id->tok.sym.str(),            /* Function name */
          &(CGF.M)                      /* Module = 0 */
          );
    }

    /* Store the function value in the entity. */
    entity->value = func;

    if ( ! isGlobal ) // function definition
    {
      /* Set the current function in the CGF. */
      CGF.parent = func;

      /* Add a first basic block to the function, that becomes the entry point
       * for the function.  This will automatically convert the function from a
       * declaration to a definition.
       */
      std::string name( id->tok.sym.str() );
      name += ".entry";
      BasicBlock *funcEntry = CGF.getBasicBlock( name );

      /* Set the insert point for the builder to the entry of the function. */
      CGF.Builder.SetInsertPoint( funcEntry );

      /* Emit allocas for the parameters. */
      this->declarator->emit( CGF );

      /* Store the parameters. */
      {
        auto argIt = func->arg_begin();
        auto paramIt = CGF.params.begin();
        for ( ; argIt != func->arg_end() && paramIt != CGF.params.end();
            ++argIt, ++paramIt )
        {
          argIt->setName( (*paramIt)->getName() );
          CGF.Builder.CreateStore( argIt, *paramIt );
        }
      }

      /* Clear the parameter stack. */
      CGF.params.clear();
    }
    return;
  } // end function type

  if ( isGlobal )
  {
    /* Create a global variable. */
    entity->value = new GlobalVariable(
        CGF.M,                                  /* Module & */
        type,                                   /* Type * */
        false,                                  /* bool isConstant */
        GlobalValue::ExternalLinkage,           /* LinkageType */
        Constant::getNullValue(type),           /* Constant * Initializer */
        id->tok.sym.str()                       /* const Twine &Name = "" */
        );
  }
  else
  {
    /* Get the current basic block. */
    BasicBlock * const curBB = CGF.Builder.GetInsertBlock();

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
      Instruction * const alloca = new AllocaInst(
          type,             /* Type */
          0,                /* ArraySize = 0 */
          id->tok.sym.str() /* Name */
          );

      alloca->insertBefore( curBB->begin() );
      getEntity()->value = alloca;
    }
  }
}

void FunctionDef::emit( CodeGenFunction &CGF, bool /* = false */ ) const
{
  /* Create the function and its entry block.  Create allocas for the parameters
   * inside the entry block.
   */
  this->decl->emit( CGF );

  Function *func = CGF.parent;
  FunctionType *type = static_cast< FunctionType * >(
      this->decl->getEntity()->type->getLLVMType( CGF ) );

  /* Emit the content of the function. */
  this->compStmt->emit( CGF );

  BasicBlock * const curBB = CGF.Builder.GetInsertBlock();

  // Connect goto stmts with their labels.
  CGF.WireLabels();
  CGF.Builder.SetInsertPoint( curBB );

  if ( ! curBB->getTerminator() )
  {
    /* Return the return value, or void. */
    if ( type->getReturnType()->isVoidTy() )
      CGF.Builder.CreateRetVoid();
    else
      CGF.Builder.CreateRet( Constant::getNullValue( type->getReturnType() ) );
  }

  /* Remove the function as current parent and its return value from CGF. */
  CGF.parent = NULL;

  verifyFunction( *func );
}

void ParamList::emit( CodeGenFunction &CGF ) const
{
  /* Only use the last seen param list, otherwise we get in trouble with
   * functions returning function pointers */
  CGF.params.clear();
  for ( auto it : *this )
    it->emit( CGF );
}

void ParamDecl::emit( CodeGenFunction &CGF, bool /* = false */ ) const
{
  /* Get the entity of this param decl. */
  Entity * const entity = this->getEntity();

  /* if the type of this parameter is void, skip. */
  if ( TypeFactory::getVoid() == entity->type )
    return;

  /* Compute the type of this param. */
  llvm::Type *type = entity->type->getLLVMType( CGF );

  /* Obtain this param's name. */
  Identifier const * const id =
    static_cast< Identifier const * >( entity->getParent() );

  /* Create an alloca for this param. */
  entity->value = CGF.Builder.CreateAlloca( type );

  /* Set the name for this param. */
  entity->value->setName( id->tok.sym.str() );

  /* Push the param to our stack. */
  CGF.params.push_back( entity->value );
}
