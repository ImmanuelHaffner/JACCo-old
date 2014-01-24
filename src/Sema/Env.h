//===--- Environment.h-----------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the Environment interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_ENV_H
#define C4_ENV_H

#include <iostream>
#include <sstream>
#include <set>
#include <vector>
#include <unordered_map>
#include <cstring>
#include "../Support/Symbol.h"
#include "../util.h"
#include "../diagnostic.h"
#include "SemaType.h"
#include "Entity.h"


namespace C4
{
  // Forward Declarations
  namespace AST
  {
    struct TypeSpecifier;
    struct ParamList;
  }


  namespace Sema
  {
    /// Maps symbols to types 
    typedef std::unordered_map< Symbol, Type const * > TypeTable;

    /// Maps symbols to entities
    typedef std::unordered_map< Symbol, Entity const * > IdMap;

    /// \brief Defines a scope.
    ///
    /// Contains a type table, that maps identifiers to types, and a map from
    /// identifiers to entities.
    struct Scope
    {
      Scope() {}
      ~Scope() {}

      Entity const * lookup( Symbol const id ) const;
      bool insert( Symbol const id, Entity const * const entity );
      bool insert( Symbol const id, Type const * const type );

      private:
      TypeTable typeTable;
      IdMap idMap;
    };


    /// Defines an environment class, that keeps track of the scopes.
    struct Env
    {
      Env();
      ~Env();

      /// \brief Pushes a new, empty scope onto the stack.
      void pushScope();

      /// \brief Pops the topmost scope from the stack.
      void popScope();

      /// Traverses the scope stack, starting at the current scope, and searches
      /// for the first mapping for an identifier.
      ///
      /// \return the first mapped entitity, if the id was mapped, NULL
      /// otherwise
      Entity const * lookup( Symbol const id );

      /// Inserts a new mapping from id to entity to the identifier map.
      ///
      /// \return false iff the id was already mapped in the current scope, true
      /// otherwise
      bool insert( Symbol const id, Entity const * const entity );

      /// Inserts a new mapping from the identifier to the type in the type
      /// table.
      ///
      /// \return false iff the identifier was already mapped, true otherwise
      bool insert( Symbol const typeName, Type const * const type );

      private:
      std::vector< Scope > scopeStack;
    };
  }
}

#endif
