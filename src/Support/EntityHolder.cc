//===--- EntityHolder.cc --------------------------------------------------===//
//
//  ~~~ The C4 Compiler ~~~
//
//  This file implements the entity holder interface.
//
//===----------------------------------------------------------------------===//


#include "EntityHolder.h"

#include <cassert>
#include <iostream>
#include "Entity.h"
#include "../AST/Printable.h"


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

void EntityHolder::dump() const
{
  if ( auto me = dynamic_cast< AST::Printable const * >( this ) )
    me->dump();
  else
    std::cout << "ERROR: not a printable object" << std::endl;
}
