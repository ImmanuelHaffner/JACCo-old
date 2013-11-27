//===--- StringLiteral.h --------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_STRING_LITERAL_H
#define C4_STRING_LITERAL_H

#include <iostream>

#include "Expression.h"
#include "../Lex/Token.h"


namespace C4
{
  namespace AST
  {
    ///
    struct StringLiteral : Expression
    {
      explicit StringLiteral( Lex::Token const tok );
      ~StringLiteral() {}

      friend std::ostream & operator<<( std::ostream &out,
          StringLiteral const &lit );

      Lex::Token const tok;
      void accept ( ASTNodeVisitor & visitor );
    }; // end struct Variable

    std::ostream & operator<<( std::ostream &out, StringLiteral const &lit );
  } // end namespace AST
} // end namespace C4

#endif
