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

#include "Expr.h"
#include "../Lex/Token.h"


namespace C4
{
  namespace AST
  {
    ///
    struct Variable : Expr
    {
      explicit Variable( Lex::Token const &tok ) : Expr(tok)
      {
        assert( tok.kind == Lex::TK::IDENTIFIER
            && "token must be an identifier" );
      }

      ~Variable() {}

      void print( Printer const p ) const;

      friend std::ostream & operator<<( std::ostream &out,
          Variable const &var );
    }; // end struct Variable

    std::ostream & operator<<( std::ostream &out, Variable const &var );
  } // end namespace AST
} // end namespace C4

#endif
