//===--- Env.cc------------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements the Environment interface.
//
//===----------------------------------------------------------------------===//


#include "Env.h"

#include <cassert>


using namespace C4;
using namespace AST;
using namespace Sema;


Entity * Scope::lookup( Symbol const id ) const
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

Entity * Scope::insert( Symbol const id )
{
  // Check whether id is already mapped.
  if ( idMap.find( id ) != idMap.end() )
    return NULL;

  Entity * entity = new Entity();
  idMap.insert( std::pair< Symbol, Entity * >( id, entity ) );
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

IdMap Scope::getIdMap()
{
  return idMap;
}


void Env::pushScope()
{
  scopeStack.push_back( new Scope() );
}

void Env::pushScope( Scope * const scope )
{
  scopeStack.push_back( scope );
}

Scope * Env::popScope()
{
  assert( scopeStack.size() > 1 && "cannot pop the global scope" );
  Scope * const scope = scopeStack.back();
  scopeStack.pop_back();
  return scope;
}

Scope * Env::topScope()
{
  Scope * const scope = scopeStack.back();
  return scope;
}

Entity * Env::lookup( Symbol const id )
{
  // iterate over all scopes, starting with the last
  for ( auto scope = scopeStack.rbegin(); scope != scopeStack.rend(); ++scope )
  {
    Entity * const entity = (*scope)->lookup( id );
    if ( entity ) return entity;
  }
  return NULL;
}

Type const * Env::lookupType( Symbol const id )
{
  for ( auto scope = scopeStack.rbegin(); scope != scopeStack.rend(); ++scope )
  {
    Type const *type = (*scope)->lookupType( id );
    if ( type ) return type;
  }
  return NULL;
}

Entity * Env::insert( Symbol const id )
{
  // Insert into the top-most scope.
  return scopeStack.back()->insert( id );
}

bool Env::insert( Symbol const id, Type const * const type )
{
  // Insert into the top-most scope.
  return scopeStack.back()->insert( id, type );
}

void Env::pushFunction( Entity * e )
{
  functionStack.push_back( e );
  // Create label scope for this function
  std::pair< Labels, Targets > setPair = std::make_pair( Labels(),
      Targets() );
  labelScopes.insert( std::pair< Entity *, std::pair< Labels, Targets > >
        ( e, setPair ) );
}

Entity * Env::topFunction()
{
  return functionStack.back();
}

Entity * Env::popFunction()
{
  Entity * e = functionStack.back();
  functionStack.pop_back();
  return e;
}

Labels * Env::getLabelSymbols()
{
  return &( labelScopes.find( topFunction() )->second.first );
}

Targets * Env::getGotoTokens()
{
  return & ( labelScopes.find( topFunction() )->second.second );
}

void Env::insertGoto( Lex::Token const * tok )
{
  getGotoTokens()->push_back( tok );
}

Lex::Token const * Env::insertLabel( Lex::Token const * tok )
{
  Labels * labels = getLabelSymbols();
  auto elem = labels->find( tok->sym );
  if ( elem != labels->end() )
    return (*elem).second;
  labels->insert( std::make_pair( tok->sym, tok ) );
  return tok;
}
