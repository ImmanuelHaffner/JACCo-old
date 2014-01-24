#ifndef C4_ENTITY_H
#define C4_ENTITY_H

#include "SemaType.h"

namespace C4
{
  namespace Sema
  {
    /// \brief Used to map identifiers to types, values, and anything else.
    struct Entity
    {
      Entity() {}

      Entity( Type const * const type ) :
        type(type)
      {}

      Type const * type;
    };
  }
}

#endif
