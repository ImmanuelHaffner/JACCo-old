//===--- EntityHolder.cc --------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements the entity holder interface.
//
//===----------------------------------------------------------------------===//


#include "EntityHolder.h"
#include <assert.h>

using namespace C4;
using namespace Sema;


void EntityHolder::attachEntity(Entity const * entity)
{
  if ( ! entity )
    throw EntityHolderException(); // REVIEW don't we want to assert instead of
                                   // throwing an exception

  this->entity = entity;
}

Entity const* EntityHolder::getEntity()
{
  return entity;
}
