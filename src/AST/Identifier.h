//===--- Identifier.h -----------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the Abstract Syntax tree interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_IDENTIFIER_H
#define C4_IDENTIFIER_H

#include "AST.h"
#include "../Lex/IdentifierToken.h"

namespace C4
{
  namespace AST
  {
    ///
    struct Identifier : ASTNode
    {
      Identifier( Lex::IdentifierToken &token, ASTNode * const parent = NULL );
      ~Identifier();

      friend std::ostream & operator<<( std::ostream &out,
          Identifier const &node );
      virtual void dump() const;

      private:
      Lex::IdentifierToken &token;
    };
  }
}

#endif
