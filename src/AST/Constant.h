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
#include "../Lex/ConstantToken.h"

namespace C4
{
  namespace AST
  {
    ///
    struct Constant : ASTNode
    {
      Constant( Lex::ConstantToken &token, ASTNode * const parent = NULL );
      ~Constant();

      friend std::ostream & operator<<( std::ostream &out,
          Constant const &node );
      virtual void dump() const;

      private:
      Lex::ConstantToken &token;
    };
  }
}

#endif
