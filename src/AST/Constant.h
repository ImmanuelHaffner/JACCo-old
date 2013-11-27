//===--- Constant.h -------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_CONSTANT_H
#define C4_CONSTANT_H

#include <iostream>

#include "Expression.h"
#include "../Lex/Token.h"


namespace C4
{
  namespace AST
  {
    ///
    struct Constant : Expression
    {
      explicit Constant( Lex::Token const tok );
      ~Constant() {}

      friend std::ostream & operator<<( std::ostream &out,
          Constant const &con );

      Lex::Token const tok;
      void accept ( ASTNodeVisitor & visitor );
    }; // end struct Variable

    std::ostream & operator<<( std::ostream &out, Constant const &con );

  } // end namespace AST
} // end namespace C4

#endif
