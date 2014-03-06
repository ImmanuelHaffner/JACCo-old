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


/* Forward declarations */
namespace C4
{
  struct EntityHolder;
}

namespace llvm
{
  class Value;
}


namespace C4
{
  /// \brief Used to map identifiers to types, values, and anything else.
  struct Entity
  {
    friend struct EntityHolder;

    Entity() {}

    ~Entity() {}

    inline EntityHolder const * getParent() const
    {
      return parent;
    }

    Sema::Type const *type = NULL;
    bool global = false;
    bool defined = false;
    llvm::Value *value = NULL;

    private:
    EntityHolder const *parent = NULL;

    void attachParent( EntityHolder const * const p )
    {
      assert( ! this->parent && "the entity already has a parent" );
      parent = p;
    }

  };
} // end namespace C4


#endif
