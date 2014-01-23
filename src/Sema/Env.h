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
    typedef std::unordered_map< Symbol, Type const * const > TypeTable;

    /// Maps symbols to entities
    typedef std::unordered_map< Symbol, Entity const * const > IdMap;

    /// A scope contains a type table and a mapping from symbols to SemaTypes
    typedef std::pair< TypeTable, IdMap > Scope;

    /// Defines an environment class, that keeps track of the scopes.
    struct Env
    {
      Env();
      ~Env();

      void pushScope();
      void popScope();

      Entity const * lookup( Symbol const id );
      bool insert( Symbol const id, Entity const * const entity );
      bool addType( Symbol const type_id, Type const * const type );

      private:
      std::vector< Scope > scopeStack;
    };
  }
}

#endif
