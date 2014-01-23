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
  for ( auto scopeIt = scopeStack.rbegin(); scopeIt != scopeStack.rend();
      ++scopeIt )
  {
    auto find_it = scopeIt->second.find( id );
    if ( find_it != scopeIt->second.end() )
      return find_it->second;
  }
  return NULL;
}

bool Env::insert( Symbol const id, Entity const * const entity )
{
  IdMap & topIdMap = scopeStack.back().second;
  auto find_it = topIdMap.find( id );
  if ( find_it != topIdMap.end() )
    return false;
  topIdMap.insert( std::make_pair( id, entity ) );
  return true;
}

bool Env::addType( Symbol const type_id, Type const * const type )
{
  TypeTable & topTypeTable = scopeStack.back().first;
  auto find_it = topTypeTable.find( type_id );
  if ( find_it != topTypeTable.end() )
    return false;
  topTypeTable.insert( std::make_pair( type_id, type ) );
  return true;
}
