//===--- Locatable.h -----------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_LOCATABLE_H
#define C4_LOCATABLE_H

#include <iostream>
#include "../Lex/Token.h"


namespace C4
{
  namespace AST
  {
    ///
    struct Locatable
    {
      Locatable( Lex::Token const &tok ) : tok(tok) {}
      virtual ~Locatable() {}

      friend std::ostream & operator<<( std::ostream &out,
          Locatable const &loc );

      Lex::Token const tok;
    }; // end struct Locatable

    std::ostream & operator<<( std::ostream &out, Locatable const &loc );
  } // end namespace AST
} // end namespace C4

#endif
