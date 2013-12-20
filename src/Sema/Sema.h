//===--- Sema.h -----------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the SemaObject interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_SEMA_H
#define C4_SEMA_H

#include <cstring>
#include "Env.h"

namespace C4
{
  // Forward Declarations
  namespace AST
  {
    struct TypeSpecifier;
  }

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

    struct SemaType
    {
      SemaType( AST::TypeSpecifier const * const returnType,
          size_t const pointerCount = 0,
          AST::ParamList const * const paramTypes = NULL )
        : returnType(returnType), pointerCount(pointerCount),
        paramTypes(paramTypes)
      {}

      ~SemaType() {}

      AST::TypeSpecifier const * const returnType;
      size_t const pointerCount;
      AST::ParamList const * const paramTypes;
    };

    struct SemaResult
    {
      SemaResult( Valueness const valueness, SemaType const * const type )
        : valueness(valueness), type(type)
      {}

      ~SemaResult() {}

      Valueness const valueness;
      SemaType const * const type;
    };

    /// SemaObject defines an interface for all AST nodes, that are semantically
    /// analyzable.
    struct SemaObject
    {
      virtual ~SemaObject() {}

      virtual SemaResult analyze( Env ) { return SemaResult( Valueness::RLValue, NULL ); };
    };
  } // end namespace Sema
} // end namespace C4

#endif
