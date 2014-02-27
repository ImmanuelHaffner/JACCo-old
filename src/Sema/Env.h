//===--- Environment.h-----------------------------------------------------===//
//
//  ~~~ The C4 Compiler ~~~
//
//  This file defines the Environment interface.
//
//===----------------------------------------------------------------------===//


#ifndef C4_ENV_H
#define C4_ENV_H


#include <vector>
#include <unordered_map>
#include "../Support/Symbol.h"
#include "../AST/Stmt.h"
#include "Type.h"
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
    typedef std::unordered_map< Symbol, StructType * > TypeTable;

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

      /// \return the entity the id is mapped to, or NULL if the id was not
      /// mapped
      Entity const * lookup( Symbol const id ) const;

      /// \return the type the id is mapped to, or NULL if the id was not
      /// mapped
      StructType * lookupType( Symbol const id ) const;

      /// \return a new entity for the id, if the id was not already mapped,
      /// NULL otherwise
      Entity * insert( Symbol const id );

      /// \return true iff the id was not already mapped, false otherwise
      bool insert( Symbol const id, StructType * const type );

      /// \return the identifier map
      IdMap getIdMap();

      private:
      TypeTable typeTable;
      IdMap idMap;
    };


    /// Defines an environment class, that keeps track of the scopes.
    struct Env
    {
      Env() { pushScope(); /* create global scope */ }
      ~Env() {}

      /// \brief Pushes a new, empty scope onto the stack.
      void pushScope();

      /// \brief Pushes the given scope onto the stack.
      void pushScope( Scope scope );
      
      /// \brief Pops the topmost scope from the stack.
      Scope popScope();

      /// \return the depth of the scope stack, including the global scope
      inline size_t depth() const { return scopeStack.size(); }

      /// Traverses the scope stack, starting at the current scope, and searches
      /// for the first mapping for an identifier.
      ///
      /// \return the first mapped entitity, if the id was mapped, NULL
      /// otherwise
      Entity const * lookup( Symbol const id );

      /// Traveres the scope stack, starting at the current scope, and searches
      /// for the first mapping for a type identifier.
      ///
      /// \return the first mapped type, if the id was mapped, NULL otherwise
      StructType * lookupType( Symbol const id );

      /// Inserts a new mapping from id to a new created entity to the
      /// identifier map.
      ///
      /// \return NULL iff the id was already mapped in the current scope, the 
      /// pointer to the created entity otherwise
      Entity * insert( Symbol const id );

      /// Inserts a new mapping from the identifier to the type in the type
      /// table.
      ///
      /// \return false iff the identifier was already mapped, true otherwise
      bool insert( Symbol const typeName, StructType * const type );
      
      private:
      std::vector< Scope > scopeStack;
      std::vector< AST::IterationStmt > iterStmtStack;
    };
  }
}


#endif
