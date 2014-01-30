//===--- SemaTypeFactory.h ------------------------------------------------===//
//
//  ~~~ The C4 Compiler ~~~
//
//  This file declares a factory to construct sema types from the AST.
//
//===----------------------------------------------------------------------===//


#ifndef C4_SEMA_TYPE_FACTORY_H
#define C4_SEMA_TYPE_FACTORY_H

#include "SemaType.h"

#include <functional>
#include <unordered_set>
#include "../AST/Decl.h"
#include "../AST/Type.h"


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
      inline bool operator()( PtrType const * const t0,
          PtrType const * const t1 ) const
      {
        return t0->innerType == t1->innerType;
      }
    };


    /// \brief Constructs types for semantic analysis.
    ///
    /// Except for structure types, the factory returns internalized type
    /// objects.  The type factory keeps a set of all constructed types.
    struct TypeFactory
    {
      /// Destroys all tables of internalized types, as well as their elements.
      static void destroy();

      /// \return the size of the table of internalized function types
      static inline size_t sizeF()
      {
        return funcTable.size();
      }

      /// \return the size of the table of internalized function types
      static inline size_t sizeP()
      {
        return ptrTable.size();
      }


      /// \return the void type
      static Type const * getVoid();

      /// \return the char type
      static Type const * getChar();

      /// \return the int type
      static Type const * getInt();

      /// \brief Creates a new internalized pointer type, with the given inner
      /// type.
      ///
      /// \return the new pointer type
      static Type const * getPtr( Type const * const innerType );

      /// \brief Creates a new internalized function type, given the return type
      /// and the argument types.
      ///
      /// \return the new function type
      static Type const * getFunc( Type const * retType,
          std::vector< Type const * > &argTypes );

      /// \brief Creates a new internalized structure type, given the parameter
      /// types.
      static Type const * getStruct(
          std::unordered_map< Symbol, Type const * > &paramTypes );

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
      static FuncTable funcTable;
      static PtrTable ptrTable;
    }; // end struct TypeFactory
  } // end namespace Sema
} // end namespace C4


#endif
