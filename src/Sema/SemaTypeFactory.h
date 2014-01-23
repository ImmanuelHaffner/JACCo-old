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
    /// Defines the hash values for unique types.
    enum HashCode
    {
      HASH_Void = 3,
      HASH_Char = 5,
      HASH_Int = 7
    };


    /* Define hash and equals for function type.
     * (necessary for internalizing)
     */
    struct FuncHash
    {
      inline size_t operator()( FuncType const * const t ) const
      {
        return t->hashCode();
      }
    };

    struct FuncEqual
    {
      bool operator()( FuncType const * const t0,
          FuncType const * const t1 ) const;
    };

    /* Define hash and equals for pointer type.
     * (necessary for internalizing)
     */
    struct PtrHash
    {
      inline size_t operator()( PtrType const * const t ) const
      {
        return t->hashCode();
      }
    };

    struct PtrEqual
    {
      bool operator()( PtrType const * const t0,
          PtrType const * const t1 ) const
      {
        return t0 == t1;
      }
    };


    /// \brief Constructs internalized types from AST nodes.
    struct TypeFactory
    {
      /// Destroys all tables of internalized types, as well as their elements.
      static void destroy();

      /// \return the size of the table of internalized function types
      static inline size_t sizeF()
      {
        return funcTable_.size();
      }

      /// \return the size of the table of internalized function types
      static inline size_t sizeP()
      {
        return ptrTable_.size();
      }


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

      // The hash sets to internalize and function types and pointer types.
      typedef std::unordered_set< FuncType const *, FuncHash, FuncEqual >
        FuncTable;
      typedef std::unordered_set< PtrType const *, PtrHash, PtrEqual >
        PtrTable;
      static FuncTable funcTable_;
      static PtrTable ptrTable_;
    }; // end struct TypeFactory
  } // end namespace Sema
} // end namespace C4


#endif
