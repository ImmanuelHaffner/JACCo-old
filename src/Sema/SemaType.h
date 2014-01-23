//===--- SemaType.h -------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file declares the semantic types.
//
//===----------------------------------------------------------------------===//

#ifndef C4_SEMA_TYPE_H
#define C4_SEMA_TYPE_H

#include <vector>
#include <functional>
#include <cstring>
#include <string>
#include <unordered_set>

namespace C4
{
  namespace Sema
  {
    /// \brief Represents types for semantical analysis.
    ///
    /// Types are partitioned into object types (types that describe objects)
    /// and function types (types that describe functions).
    struct Type
    {
      virtual ~Type() {}
    }; // end struct Type


    /// \brief Represents function types.
    struct FuncType : Type
    {
      FuncType( Type const * const retType,
          std::vector< Type const * > argTypes ) :
        retType(retType)
      {
        this->argTypes.insert( this->argTypes.end() /* where to insert */,
            argTypes.begin() /* begin of elements to insert */,
            argTypes.end() /* end of elements to insert */ );
      }

      ~FuncType() {}

      Type const * const retType;

      private:
      std::vector< Type const * > argTypes;
    }; // end struct FuncType

    /// \brief Represents pointer and scalar types.
    ///
    /// At various points within a translation unit an object type may be
    /// incomplete (lacking sufficient information to determine the size of
    /// objects of that type) or complete (having sufficient information).
    struct ObjType : Type
    {
      /// States whether an object is complete. Incomplete objects are not yet
      /// completely constructed. Hence, it is impossible to compute their size.
      ///
      /// \return true iff the object is complete, false otherwise
      virtual bool isComplete() = 0;

      /// \return the size of the object in bytes
      virtual size_t size() const = 0;
    }; // end struct ObjType


    /// \brief The void type comprises an empty set of values; it is an
    /// incomplete object type that cannot be completed.
    struct VoidType : ObjType
    {
      VoidType() {}
      ~VoidType() {}

      inline bool isComplete() { return false; }
      inline size_t size() const { return -1; } // since Void is incomplete, the
                                                // size is irrelevant
    }; // end struct VoidType


    /// \brief A structure type describes a sequentially allocated nonempty set
    /// of member objects (and, in certain circumstances, an incomplete array),
    /// each of which has an optionally specified name and possibly distinct
    /// type.
    struct StructType : ObjType
    {
      StructType( std::vector< Type const * > const content )
      {
        this->content.insert( this->content.end() /* where to insert */,
            content.begin() /* begin of elements to insert */,
            content.end() /* end of elements to insert */ );
      }

      ~StructType() {}

      inline void complete() { completed = true; }
      inline bool isComplete() { return completed; }
      inline size_t size() const
      {
        return completed ? content.size() : -1;
      }

      private:
      bool completed;
      std::vector< Type const * > content;
    }; // end struct StructType


    /// \brief Arithmetic types and pointer types are collectively called scalar
    /// types.
    struct ScalarType : ObjType
    {
    }; // end struct ScalarType


    struct PtrType : ScalarType
    {
      PtrType( Type const * const innerType ) :
        innerType(innerType)
      {}

      ~PtrType() {}

      inline bool isComplete() { return true; }

      Type const * const innerType;
    }; // end struct PtrType


    /// \brief Integer and floating types are collectively called arithmetic
    /// types.
    struct ArithmeticType : ScalarType
    {
    }; // end struct ArithmeticType


    /// The type char, the signed and unsigned integer types, and the floating
    /// types are collectively called the basic types.  The basic types are
    /// complete object types.
    ///
    /// Even if the implementation defines two or more basic types to have the
    /// same representation, they are nevertheless different types.
    struct BasicType : ArithmeticType
    {
      BasicType( size_t const size ) : _size(size) {}
      ~BasicType() {}

      inline bool isComplete() { return true; }
      inline size_t size() const { return _size; }

      private:
      size_t const _size; // the size in bytes
    }; // end struct BasicType
  } // end namespace Sema
} // end namespace C4

#endif
