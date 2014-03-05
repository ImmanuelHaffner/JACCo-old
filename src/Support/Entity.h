//===--- Entity.h ---------------------------------------------------------===//
//
//  ~~~ The C4 Compiler ~~~
//
//  This file declares the entity object.
//
//  The entity is used to connect AST nodes with types or LLVM values.
//
//===----------------------------------------------------------------------===//


#ifndef C4_ENTITY_H
#define C4_ENTITY_H


#include "../Sema/Type.h"


namespace C4
{
  // Forward declarations
  struct EntityHolder;

  /// \brief Used to map identifiers to types, values, and anything else.
  struct Entity
  {
    Entity() {}

    ~Entity() {}

    void attachParent( EntityHolder const * const p )
    {
      assert( ! this->parent && "the entity already has a parent" );
      parent = p;
    }

    inline EntityHolder const * getParent() const
    {
      return parent;
    }

    Sema::Type const *type = NULL;
    bool global = false;
    bool defined = false;

    private:
    EntityHolder const *parent;
  };
} // end namespace C4


#endif
