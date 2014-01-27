//===--- Env.cc------------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements the Environment interface.
//
//===----------------------------------------------------------------------===//


#include "Env.h"


using namespace C4;
using namespace AST;
using namespace Sema;


Entity const * Scope::lookup( Symbol const id ) const
{
  auto elem = idMap.find( id );
  if ( elem == idMap.end() )
    return NULL;
  return elem->second;
}

Type const * Scope::lookupType( Symbol const id ) const
{
  auto elem = typeTable.find( id );
  if ( elem == typeTable.end() )
    return NULL;
  return elem->second;
}

Entity const * Scope::insert( Symbol const id )
{
  // Check whether id is already mapped.
  if ( idMap.find( id ) != idMap.end() )
    return NULL;

  Entity const * entity = new Entity();
  idMap.insert( std::pair< Symbol, Entity const * >( id, entity ) );
  return entity;
}

bool Scope::insert( Symbol const id, Type const * const type )
{
  // Check whether id is already mapped.
  if ( typeTable.find( id ) != typeTable.end() )
    return false;

  typeTable.insert( std::pair< Symbol, Type const * >( id, type ) );
  return true;
}


void Env::pushScope()
{
  scopeStack.push_back( Scope() );
}

void Env::popScope()
{
  scopeStack.pop_back();
}

Entity const * Env::lookup( Symbol const id )
{
  // iterate over all scopes, starting with the last
  for ( auto scope = scopeStack.rbegin(); scope != scopeStack.rend(); ++scope )
  {
    Entity const * const entity = scope->lookup( id );
    if ( entity ) return entity;
  }
  return NULL;
}

Type const * Env::lookupType( Symbol const id )
{
  for ( auto scope = scopeStack.rbegin(); scope != scopeStack.rend(); ++scope )
  {
    Type const * const type = scope->lookupType( id );
    if ( type ) return type;
  }
  return NULL;
}

Entity const * Env::insert( Symbol const id )
{
  // Obtain the topmost scope.
  Scope &scope = scopeStack.back();
  return scope.insert( id );
}

bool Env::insert( Symbol const id, Type const * const type )
{
  // Obtain the topmost scope.
  Scope &scope = scopeStack.back();
  return scope.insert( id, type );
}
