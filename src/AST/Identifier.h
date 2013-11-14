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
#include "../Lex/Token.h"

namespace C4
{
  namespace AST
  {
    ///
    struct Identifier : ASTNode
    {
      Identifier( Lex::Token const &tok, ASTNode * const parent = NULL );
      ~Identifier();

      friend std::ostream & operator<<( std::ostream &out,
          Identifier const &node );
      void dump( std::ostream &out = std::cout, int const n = 0 ) const;

      Lex::Token const tok;
    };
  }
}

#endif
