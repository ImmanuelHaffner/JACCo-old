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
#include <unordered_map>
#include <utility>
#include <cstring>
#include "../util.h"
#include "../diagnostic.h"
#include "../AST/AST.h"


namespace C4
{
  namespace Sema
  {
    typedef std::vector< AST::TypeSpecifier const * > TypeTable;
    typedef std::map< std::string, std::pair< AST::TypeSpecifier const * const,
            AST::ParamList const * const > > IdMap;
    typedef std::pair< TypeTable, IdMap > Scope;
    struct Env
    {
      Env();
      ~Env();

      void pushScope();
      void popScope();
      AST::TypeSpecifier const * const lookup( std::string id );
      bool insert( std::string id, AST::TypeSpecifier const * const typeSpec,
          AST::ParamList const * const paramList );
      bool addType( AST::TypeSpecifier const * const typeSpec );

      private:

      std::vector< Scope > scopeStack; 
    };
  }
}

#endif
