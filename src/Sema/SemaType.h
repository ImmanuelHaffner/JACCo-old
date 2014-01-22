//===--- SemaType.h -------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file declares the semantic types.
//
//===----------------------------------------------------------------------===//

#ifndef C4_SEMA_TYPE_H
#define C4_SEMA_TYPE_H

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
      virtual size_t hash() = 0;
    }; // end struct Type


    /// \brief Represents function types.
    struct FuncType : Type
    {
    }; // end struct FuncType

    /// \brief Represents pointer and scalar types.
    ///
    /// At various points within a translation unit an object type may be
    /// incomplete (lacking sufficient information to determine the size of
    /// objects of that type) or complete (having sufficient information).
    struct ObjType : Type
    {
      virtual bool isComplete() = 0;
    }; // end struct ObjType


    /// \brief The void type comprises an empty set of values; it is an
    //incomplete object type that cannot be completed.
    struct VoidType : ObjType
    {
      inline bool isComplete() { return false; }
    }; // end struct VoidType

    /// \brief A structure type describes a sequentially allocated nonempty set
    /// of member objects (and, in certain circumstances, an incomplete array),
    /// each of which has an optionally specified name and possibly distinct
    /// type.
    struct StructType : ObjType
    {
    }; // end struct StructType


    /// \brief Arithmetic types and pointer types are collectively called scalar
    /// types.
    struct ScalarType : ObjType
    {
    }; // end struct ScalarType


    struct PtrType : ScalarType
    {
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
    }; // end struct BasicType
  } // end namespace Sema
} // end namespace std

#endif
