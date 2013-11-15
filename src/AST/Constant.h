//===--- Constant.h -------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the Abstract Syntax tree interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_CONSTANT_H
#define C4_CONSTANT_H

#include "AST.h"
#include "../Lex/Token.h"

namespace C4
{
  namespace AST
  {
    ///
    struct Constant : ASTNode
    {
      Constant( Lex::Token const &tok, ASTNode * const parent = NULL );
      ~Constant();

      friend std::ostream & operator<<( std::ostream &out,
          Constant const &node );
      void dump( std::ostream &out = std::cout, int const n = 0 ) const;

      Lex::Token const tok;
    };

    std::ostream & operator<<( std::ostream &out, Constant const &node );
  }
}

#endif
