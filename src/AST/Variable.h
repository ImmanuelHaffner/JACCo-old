//===--- Variable.h -------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_VARIABLE_H
#define C4_VARIABLE_H

#include <iostream>

#include "Expression.h"
#include "../Lex/Token.h"


namespace C4
{
  namespace AST
  {
    ///
    struct Variable : Expression
    {
      explicit Variable( Lex::Token tok );
      ~Variable() {}

      friend std::ostream & operator<<( std::ostream &out,
          Variable const &var );

      private:
      Lex::Token tok;
    }; // end struct Variable

    std::ostream & operator<<( std::ostream &out, Variable const &var );
  } // end namespace AST
} // end namespace C4

#endif
