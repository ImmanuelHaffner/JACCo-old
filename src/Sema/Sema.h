//===--- Sema.h -----------------------------------------------------------===//
//
//  ~~~ The C4 Compiler ~~~
//
//  This file defines the SemaObject interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_SEMA_H
#define C4_SEMA_H

#include <cstring>
#include "Env.h"

namespace C4
{
  /// The Sema
  namespace Sema
  {
    /// Descsribes the type of value of
    enum Valueness
    {
      LValue,
      RValue,
      RLValue
    };
  } // end namespace Sema
} // end namespace C4

#endif
