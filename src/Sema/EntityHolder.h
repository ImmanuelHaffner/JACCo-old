#ifndef C4_ENTITY_HOLDER_H
#define C4_ENTITY_HOLDER_H

#include "Entity.h"

namespace C4
{
  namespace Sema
  {
    struct EntityHolderException : std::exception
    {
      const char* what() const noexcept
      {
        return "EntityHolder::attachEntity called more than once.";
      }
    };

    struct EntityHolder
    {
      EntityHolder() :
        entity(NULL), isCalled(false)
      {}

      /// \brief Can only be called once, otherwise asserts.
      void attachEntity(Entity* entity);

      Entity const* getEntity();

    private:
      Entity const * entity;
      bool isCalled;
    };
  }
}

#endif