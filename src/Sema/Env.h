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
#include "../Support/Entity.h"
#include "../Lex/Token.h"
#include "Type.h"


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
    typedef std::unordered_map< Symbol, Entity * > IdMap;

    /// Labels 
    typedef std::unordered_map< Symbol, Lex::Token const * > Labels;

    /// Goto targets 
    typedef std::vector< Lex::Token const * > Targets;

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
      Entity * lookup( Symbol const id ) const;

      /// \return the type the id is mapped to, or NULL if the id was not
      /// mapped
      Type const * lookupType( Symbol const id ) const;

      /// \return a new entity for the id, if the id was not already mapped,
      /// NULL otherwise
      Entity * insert( Symbol const id );

      /// \return true iff the id was not already mapped, false otherwise
      bool insert( Symbol const id, Type const * const type );

      /// \return the identifier map
      IdMap getIdMap();

      private:
      TypeTable typeTable;
      IdMap idMap;
    };


    /// Defines an environment class, that keeps track of the scopes.
    struct Env
    {
      Env() { pushScope(); /* create global scope */ pushFunction( NULL ); }
      ~Env() {}

      /// \brief Pushes a new, empty scope onto the stack.
      void pushScope();

      /// \brief Pushes the given scope onto the stack.
      void pushScope( Scope * const scope );

      /// \brief Pops the topmost scope from the stack.
      Scope * popScope();

      /// \brief Returns a pointer to the top scope
      Scope * topScope();

      /// \return the depth of the scope stack, including the global scope
      inline size_t depth() const { return scopeStack.size(); }

      /// Traverses the scope stack, starting at the current scope, and searches
      /// for the first mapping for an identifier.
      ///
      /// \return the first mapped entitity, if the id was mapped, NULL
      /// otherwise
      Entity * lookup( Symbol const id );

      /// Traveres the scope stack, starting at the current scope, and searches
      /// for the first mapping for a type identifier.
      ///
      /// \return the first mapped type, if the id was mapped, NULL otherwise
      Type const * lookupType( Symbol const id );

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
      bool insert( Symbol const typeName, Type const * const type );

      /// push entity of function currently parsed
      void pushFunction( Entity * );

      /// \return entitiy of the function currently parsed
      Entity * topFunction();

      /// Returns the entity of the currently parsed function, and removes it
      /// from the stack.
      ///
      /// \return entitiy of function currently parsed
      Entity * popFunction();

      /// \return set of labels in the current function
      Labels * getLabelSymbols();

      /// \return set of goto targets in the current function
      Targets * getGotoTokens(); 

      void insertGoto( Lex::Token const * tok );
      Lex::Token const * insertLabel( Lex::Token const * tok );

      private:
      std::vector< Scope * > scopeStack;
      std::vector< Entity * > functionStack;
      std::unordered_map< Entity *, std::pair< Labels, Targets > >
        labelScopes;
    };
  }
}


#endif
