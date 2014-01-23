#ifndef C4_ENTITY_H
#define C4_ENTITY_H

#include "SemaType.h"

namespace C4
{
  namespace Sema
  {
    struct Entity
    {
      inline Entity(Type* type)
      {
        this->type = type;
      }
      Type* getType()
      {
        return type;
      }

    private:
      Type *type;
    };
  }
}

#endif
