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
#include <unordered_map>
#include "../Support/Symbol.h"

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

      virtual size_t hashCode() const = 0;
    }; // end struct Type


    /// \brief Represents function types.
    struct FuncType : Type
    {
      FuncType( Type const * const retType,
          std::vector< Type const * > argTypes ) :
        retType(retType), argTypes(argTypes)
      {}

      ~FuncType() {}

      inline size_t hashCode() const
      {
        size_t h = retType->hashCode();
        for ( Type const * t : argTypes )
          h = h * 23 + t->hashCode();
        return h;
      }

      Type const * const retType;
      std::vector< Type const * > const argTypes;
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
      VoidType( size_t const hashCode ) : hashCode_(hashCode) {}
      ~VoidType() {}

      inline bool isComplete() { return false; }
      inline size_t size() const { return -1; } // since Void is incomplete, the
                                                // size is irrelevant

      inline size_t hashCode() const { return hashCode_; }

      private:
      size_t const hashCode_;
    }; // end struct VoidType


    /// \brief A structure type describes a sequentially allocated nonempty set
    /// of member objects (and, in certain circumstances, an incomplete array),
    /// each of which has an optionally specified name and possibly distinct
    /// type.
    struct StructType : ObjType
    {
      StructType( std::unordered_map< Symbol, Type const * > const content ) :
        content(content)
      {}

      ~StructType() {}

      inline void complete() { completed = true; }
      inline bool isComplete() { return completed; }
      inline size_t size() const
      {
        return completed ? content.size() : -1;
      }

      /// Since structure types are not internalized, we can simply return 0.
      inline size_t hashCode() const
      {
        return 0;
      }

      std::unordered_map< Symbol, Type const * > const content;

      private:
      bool completed;
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
      inline size_t size() const { return 4; }
      inline size_t hashCode() const
      {
        size_t const h = innerType->hashCode();
        return ( h * 31 ) ^ h;
      }

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
      BasicType( size_t const size, size_t const hashCode ) :
        size_(size), hashCode_(hashCode)
      {}

      ~BasicType() {}

      inline bool isComplete() { return true; }
      inline size_t size() const { return size_; }
      inline size_t hashCode() const { return hashCode_; }

      private:
      size_t const size_; // the size in bytes
      size_t const hashCode_; // the default hash for that type (MUST BE UNIQUE!)
    }; // end struct BasicType
  } // end namespace Sema
} // end namespace C4

#endif
