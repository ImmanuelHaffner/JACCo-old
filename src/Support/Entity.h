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
  /// \brief Used to map identifiers to types, values, and anything else.
  struct Entity
  {
    Entity() : type(NULL) {}

    Entity( Sema::Type const * const type ) :
      type(type)
    {}

    ~Entity() {}

    Sema::Type const * type;
  };
} // end namespace C4


#endif
