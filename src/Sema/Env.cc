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

TypeSpecifier const * Env::lookup( Symbol const id )
{
  // iterate over all scopes, starting with the last
  for ( auto scopeIt = scopeStack.rbegin(); scopeIt != scopeStack.rend();
      ++scopeIt )
  {
    // TODO get the sema type for the id
  }
  return NULL;
}

bool Env::insert( Symbol const id, SemaType const * type )
{
  // TODO
  return false;
}

bool Env::addType( TypeSpecifier const * const typeSpec )
{
  return true;
}
