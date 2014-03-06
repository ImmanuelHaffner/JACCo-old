//===--- EntityHolder.h ---------------------------------------------------===//
//
//  ~~~ The C4 Compiler ~~~
//
//  This file declares the entity holder interface.
//
//===----------------------------------------------------------------------===//


#ifndef C4_ENTITY_HOLDER_H
#define C4_ENTITY_HOLDER_H


#include <cstring>  /* NULL */


/* Forward declarations */
namespace C4
{
  struct Entity;
}

namespace C4
{
  /// \brief A super class for all AST nodes that must keep a reference to
  /// their entity.
  struct EntityHolder
  {
    EntityHolder() : entity(NULL) {}
    virtual ~EntityHolder() {}

    /// Attches an entity to this holder.
    /// Should only be called once, otherwise asserts.
    ///
    /// If the attached entity has no parent yet, makes this holder its parent.
    ///
    /// \param entity the entity to attach to this holder
    void attachEntity( Entity * const entity );

    /// \return the attached entity, or NULL if no entity was attached yet
    Entity * getEntity() const;

    private:
    Entity *entity;
  };
} // end namespace C4


#endif
