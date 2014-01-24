#include "EntityHolder.h"
#include <assert.h>

using namespace C4;
using namespace Sema;

void EntityHolder::attachEntity(Entity* entity)
{
  if(!isCalled)
  {
    this->entity = entity;
    isCalled = true;
  }
  else
  {
    throw EntityHolderException();
  }
}

Entity const* EntityHolder::getEntity()
{
  return entity;
}
