//===--- Type.h -----------------------------------------------------------===//
//
//  ~~~ The C4 Compiler ~~~
//
//  This file declares the semantic types.
//
//===----------------------------------------------------------------------===//

#ifndef C4_SEMA_TYPE_H
#define C4_SEMA_TYPE_H

#include <vector>
#include <functional>
#include <cstring>
#include <string>
#include <unordered_map>
#include <cassert>
#include "../Support/Symbol.h"
#include "TypeHelper.h"

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
      typedef std::vector< Type const * > params_t;

      FuncType( Type const * const retType, params_t params )
        : retType(retType), params(params)
      {}

      ~FuncType() {}

      inline size_t hashCode() const
      {
        size_t h = retType->hashCode();
        for ( auto it = params.begin(); it != params.end(); ++it )
          h = h * 23 + (*it)->hashCode();
        return h;
      }

      Type const * const retType;
      params_t const params;
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
      virtual bool isComplete() const = 0;

      /// \return the size of the object in bytes
      virtual size_t size() const = 0;
    }; // end struct ObjType


    /// \brief The void type comprises an empty set of values; it is an
    /// incomplete object type that cannot be completed.
    struct VoidType : ObjType
    {
      VoidType( size_t const hashCode ) : hashCode_(hashCode) {}
      ~VoidType() {}

      inline bool isComplete() const { return false; }
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
      // The data structure holding the elements of a structure type.
      typedef std::vector< Type const * > elements_t;

      StructType() : size_(-1u) {}

      StructType( elements_t const &elements ) : size_(-1u)
      {
        complete( elements );
      }

      ~StructType() {}

      /// Specifies the elements of this structure type, computes its size and
      /// marks it as completed.
      ///
      /// $6.7.2.1.3:
      /// A structure or union shall not contain a member with incomplete or
      /// function type
      inline void complete( elements_t const &elements )
      {
        assert( size_ == -1u && "structure type already completed" );

        // Iterate over all elements, accumulate their sizes and add them to
        // this structure type.
        size_ = 0;
        for ( auto it = elements.begin(); it != elements.end(); ++it )
        {
          this->elements.push_back( *it );
          ObjType const *elem = static_cast< ObjType const * >( *it );
          size_ += elem->size();
        }
      }

      inline bool isComplete() const { return size_ != -1u; }

      inline size_t size() const
      {
        return size_;
      }

      /// Structure types must not be internalized. However, they can be
      /// referenced by internalized types (e.g. pointer types). To be able to
      /// compute a hash code for the type holding a reference to a structure
      /// type, we need to have a hash code that is unique for each structure
      /// type object.
      ///
      /// \return the address of this object
      inline size_t hashCode() const
      {
        return (size_t) this;
      }

      elements_t elements;

      private:
      size_t size_;
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

      inline bool isComplete() const { return true; }
      inline bool isPointerToCompleteObj() const
      {
        return isCompleteObjType(innerType);
      }
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

      inline bool isComplete() const { return true; }
      inline size_t size() const { return size_; }
      inline size_t hashCode() const { return hashCode_; }

      private:
      size_t const size_; // the size in bytes
      size_t const hashCode_; // the default hash for that type (MUST BE UNIQUE!)
    }; // end struct BasicType
  } // end namespace Sema
} // end namespace C4

#endif
