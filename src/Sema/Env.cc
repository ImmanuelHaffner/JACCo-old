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

TypeSpecifier const * const Env::lookup( Symbol const id )
{
  for ( auto it = scopeStack.begin(); it != scopeStack.end(); ++it )
  {
    auto it2 = it->second.find ( id );
    if ( it2 != it->second.end() )
      return it2->second.first;
  }
  return NULL;
}

bool Env::insert( Symbol const id, SemaType const * type )
{
  IdMap & topIdMap = scopeStack.back().second;
  auto it = topIdMap.find( id );
  if ( it != topIdMap.end() )
    return false;
  topIdMap.insert( std::make_pair( id, std::make_pair( typeSpec, params ) ) );
  return true;
}

bool Env::addType( TypeSpecifier const * const typeSpec )
{
  TypeTable & topTypeTable = scopeStack.back().first;
  for ( auto it : topTypeTable )
  {
    if ( it->tok.kind != TK::Struct && it->tok.kind == typeSpec->tok.kind )
      return false;

    if ( auto structSpec = dynamic_cast< StructSpecifier const * const >
        ( typeSpec ) )
      if ( auto itStruct = dynamic_cast< StructSpecifier const * const >( it ) )
        if ( structSpec->name == itStruct->name )
          return false;
  }
  topTypeTable.push_back( typeSpec );
  return true;
}

#endif
