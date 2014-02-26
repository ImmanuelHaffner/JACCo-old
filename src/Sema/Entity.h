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

#include "Type.h"


namespace C4
{
  namespace Sema
  {
    /// \brief Used to map identifiers to types, values, and anything else.
    struct Entity
    {
      Entity() : type(NULL) {}

      Entity( Type const * const type ) :
        type(type)
      {}

      ~Entity() {}

      Type const * type;
    };
  } // end namespace Sema
} // end namespace C4


#endif
