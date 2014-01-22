//===--- SemaTypeFactory.h ------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file declares a factory to construct sema types from the AST.
//
//===----------------------------------------------------------------------===//


#ifndef C4_SEMA_TYPE_FACTORY_H
#define C4_SEMA_TYPE_FACTORY_H

#include "SemaType.h"

#include <functional>
#include <unordered_set>


namespace C4
{
  namespace Sema
  {
    /* Define hash and equals for struct type.
     */
    struct StructHash
    {
      size_t operator()( StructType const * const t ) const;
    };

    struct StructEqual
    {
      bool operator()( StructType const * const t0,
          StructType const * const t1 ) const;
    };

    /* Define hash and equals for struct type.
     */
    struct FuncHash
    {
      size_t operator()( FuncHash const * const t ) const;
    };

    struct FuncEqual
    {
      bool operator()( FuncHash const * const t0,
          FuncHash const * const t1 ) const;
    };


    struct TypeFactory
    {
      TypeFactory();
      ~TypeFactory() {}

      Type const * getVoid() const;
      Type const * getChar() const;
      Type const * getInt() const;
      Type const * getPtr( Type const * const innerType );

      private:
      // Constant object types.
      static VoidType const VOID;
      static BasicType const CHAR;
      static BasicType const INT;

      // The hash sets to internalize structure types and function types.
      typedef std::unordered_set< StructType const *, StructHash, StructEqual >
        StructTable;
      typedef std::unordered_set< FuncType const *, FuncHash, FuncEqual >
        FuncTable;
    }; // end struct TypeFactory
  } // end namespace Sema
} // end namespace C4

namespace std
{
}; // end namespace std

#endif
