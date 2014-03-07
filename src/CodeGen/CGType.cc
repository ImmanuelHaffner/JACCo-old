//===--- CGType.cc --------------------------------------------------------===//
//
//  ~~~ The C4 Compiler ~~~
//
//  This file implements the generation of LLVM types for Sema types.
//
//===----------------------------------------------------------------------===//


#include "CodeGen.h"
#include "../Sema/Type.h"
#include "../Sema/TypeFactory.h"


using namespace C4;
using namespace Sema;
using namespace CodeGen;
using namespace llvm;


llvm::Type * Sema::FuncType::getLLVMType( CodeGenFunction &CGF ) const
{
  if ( LLVMType ) return LLVMType;

  /* Create a vector to store all parameter types */
  std::vector< llvm::Type * > ParamTypes;

  /* Iterate over all parameters and compute and store the LLVM types. */
  for ( auto it = params.begin(); it != params.end(); ++it )
  {
    /* A void type is not used for funtion types in LLVM, skip it. */
    if ( (*it) == TypeFactory::getVoid() )
      continue;
    ParamTypes.push_back( (*it)->getLLVMType( CGF ) );
  }

  /* Create the LLVM Function Type */
  LLVMType = FunctionType::get(
      retType->getLLVMType( CGF ),  /* Return type */
      ParamTypes,                   /* Parameter types */
      false                         /* isVarArg */
      );

  return LLVMType;
}

llvm::Type * Sema::StructType::getLLVMType( CodeGenFunction &CGF ) const
{
  if ( LLVMType ) return LLVMType;

  llvm::StructType * structType = llvm::StructType::create( CGF.Context,
      /* Name */ "struct" );

  /* Create a vector of types for the types of the struct members */
  std::vector< llvm::Type * > StructMemberTypes;

  for ( auto it = elements.begin(); it != elements.end(); ++it )
  {
    StructMemberTypes.push_back( (*it)->getLLVMType( CGF ) );
  }

  structType->setBody( StructMemberTypes );

  LLVMType = structType;

  return LLVMType;
}

llvm::Type * Sema::PtrType::getLLVMType( CodeGenFunction &CGF ) const
{
  if ( LLVMType ) return LLVMType;

  LLVMType = PointerType::getUnqual( innerType->getLLVMType( CGF ) );

  return LLVMType;
}

llvm::Type * Sema::VoidType::getLLVMType( CodeGenFunction &CGF ) const
{
  return CGF.Builder.getVoidTy();
}

llvm::Type * Sema::BasicType::getLLVMType( CodeGenFunction &CGF ) const
{
  if ( LLVMType ) return LLVMType;

  if ( TypeFactory::getChar() == this )
    LLVMType = CGF.Builder.getInt8Ty();
  else if (TypeFactory::getInt() == this )
    LLVMType = CGF.Builder.getInt32Ty();
  else
    /* unknown type */
    assert( false && "unknown arithmetic type" );

  return LLVMType;
}
