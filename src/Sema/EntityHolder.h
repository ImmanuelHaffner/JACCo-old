//===--- EntityHolder.h ---------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file declares the entity holder interface.
//
//===----------------------------------------------------------------------===//


#ifndef C4_ENTITY_HOLDER_H
#define C4_ENTITY_HOLDER_H

#include "Entity.h"


namespace C4
{
  namespace Sema
  {
    struct EntityHolderException : std::exception
    {
      const char * what() const noexcept
      {
        return "EntityHolder::attachEntity called more than once.";
      }
    };


    /// \brief A super class for all AST nodes that must keep a reference to
    /// their entity.
    struct EntityHolder
    {
      EntityHolder() : entity(NULL) {}
      virtual ~EntityHolder() {}

      /// Attches an entity to this holder.
      /// Should only be called once, otherwise asserts.
      ///
      /// \param entity the entity to attach to this holder
      void attachEntity(Entity const * entity);

      /// \return the attached entity, or NULL if no entity was attached yet
      Entity const * getEntity();

      private:
      Entity const * entity;
    };
  } // end namespace Sema
} // end namespace C4


#endif
