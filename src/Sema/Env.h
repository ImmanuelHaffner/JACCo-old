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
    // Forward Declarations
    struct SemaType;

    /// Holds a set of all types for a specific scope
    typedef std::set< AST::TypeSpecifier const * > TypeTable;

    /// Maps symbols to SemaTypes
    typedef std::unordered_map< Symbol, SemaType const * > IdMap;

    /// A scope contains a type table and a mapping from symbols to SemaTypes
    typedef std::pair< TypeTable, IdMap > Scope;

    /// Defines an environment class, that keeps track of the scopes.
    struct Env
    {
      Env();
      ~Env();

      void pushScope();
      void popScope();

      AST::TypeSpecifier const * lookup( Symbol const id );
      bool insert( Symbol const id, SemaType const * type );
      bool addType( AST::TypeSpecifier const * const typeSpec );

      private:
      std::vector< Scope > scopeStack;
    };
  }
}

#endif
