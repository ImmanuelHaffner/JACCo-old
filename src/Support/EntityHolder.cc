//===--- EntityHolder.cc --------------------------------------------------===//
//
//  ~~~ The C4 Compiler ~~~
//
//  This file implements the entity holder interface.
//
//===----------------------------------------------------------------------===//


#include "EntityHolder.h"
#include <cassert>


using namespace C4;
using namespace Sema;


void EntityHolder::attachEntity( Entity * const entity )
{
  // check that entity was not assigned yet
  assert( ! this->entity &&
      "an entity has already been assigned to this holder ");

  this->entity = entity;

  // If the entity does not yet have a parent, make this holder the parent.
  if ( ! entity->getParent() )
    entity->attachParent( this );
}

Entity * EntityHolder::getEntity() const
{
  return entity;
}
