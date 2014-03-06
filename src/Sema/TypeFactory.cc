//===--- TypeFactory.cc ---------------------------------------------------===//
//
//  ~~~ The C4 Compiler ~~~
//
//  This file implements a factory to construct sema types from the AST.
//
//===----------------------------------------------------------------------===//


#include "TypeFactory.h"

#include "../Lex/Token.h"


using namespace C4;
using namespace Lex;
using namespace AST;
using namespace Sema;


bool FuncEqual::operator()( FuncType const * const t0,
    FuncType const * const t1 ) const
{
  // Compare return types.
  if ( t0->retType != t1->retType ) return false;

  // Compare the argument types.
  FuncType::params_t const &params0 = t0->params;
  FuncType::params_t const &params1 = t1->params;

  if ( params0.size() != params1.size() ) return false;

  // Compare argument types.
  for ( auto it0 = params0.begin(), it1 = params1.begin();
      it0 != params0.end() && it1 != params1.end();
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


Sema::Type const * TypeFactory::getVoid() { return &VOID; }

Sema::Type const * TypeFactory::getChar() { return &CHAR; }

Sema::Type const * TypeFactory::getInt() { return &INT; }

Sema::Type const * TypeFactory::getPtr( Type const * const innerType )
{
  PtrType const * const ptr = new PtrType( innerType );

  // Internalize.
  auto it = ptrTable.find( ptr );
  if ( it != ptrTable.end() )
  {
    delete ptr;
    return *it;
  }
  ptrTable.insert( ptr );
  return ptr;
}

Sema::Type const * TypeFactory::getFunc( Type const * const retType,
    FuncType::params_t &params )
{
  FuncType const * const func = new FuncType( retType, params );

  // Internalize.
  auto it = funcTable.find( func );
  if ( it != funcTable.end() )
  {
    delete func;
    return *it;
  }
  funcTable.insert( func );
  return func;
}

Sema::Type * TypeFactory::getStruct(
    StructType::elements_t const &params )
{
  return new StructType( params );
}

Sema::Type * TypeFactory::getStruct()
{
  return new StructType();
}
