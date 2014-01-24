//===--- SemaTypeFactory.cc -----------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements a factory to construct sema types from the AST.
//
//===----------------------------------------------------------------------===//


#include "SemaTypeFactory.h"


using namespace C4;
using namespace Sema;


bool FuncEqual::operator()( FuncType const * const t0,
    FuncType const * const t1 ) const
{
  // Compare return types.
  if ( t0->retType != t1->retType ) return false;

  // Compare the argument types.
  std::vector< Type const * > const &args0 = t0->argTypes;
  std::vector< Type const * > const &args1 = t1->argTypes;

  if ( args0.size() != args1.size() ) return false;

  // Compare argument types.
  for ( auto it0 = args0.begin(), it1 = args1.begin();
      it0 != args0.end() && it1 != args1.end();
      ++it0, ++it1 )
    if ( *it0 != *it1 ) return false;

  return true;
}


void TypeFactory::destroy()
{
  // clear the function type table
  for ( auto t : funcTable )
    delete t;
  funcTable.clear();

  // clear the pointer type table
  for ( auto t : ptrTable )
    delete t;
  ptrTable.clear();
}


// Initialize the function type table.
TypeFactory::FuncTable TypeFactory::funcTable(255);
TypeFactory::PtrTable TypeFactory::ptrTable(255);


// Initialize simple types.
VoidType const TypeFactory::VOID(HASH_Void);
BasicType const TypeFactory::CHAR(1 /* size */, HASH_Char);
BasicType const TypeFactory::INT(4 /* size */, HASH_Int);


TypeFactory::TypeFactory()
{
}

Type const * TypeFactory::getVoid() const { return &VOID; }

Type const * TypeFactory::getChar() const { return &CHAR; }

Type const * TypeFactory::getInt() const { return &INT; }

Type const * TypeFactory::getPtr( Type const * const innerType )
{
  PtrType const * const ptr = new PtrType( innerType );
  auto it = ptrTable.find( ptr );
  if ( it != ptrTable.end() )
  {
    delete ptr;
    return *it;
  }
  ptrTable.insert( ptr );
  return ptr;
}

Type const * TypeFactory::getStruct( void )
{
  // TODO implement
  return NULL;
}

Type const * TypeFactory::getFunc( void )
{
  // TODO implement
  return NULL;
}
