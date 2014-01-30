//===--- Locatable.h -----------------------------------------------------===//
//
//  ~~~ The C4 Compiler ~~~
//
//  This file defines the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_LOCATABLE_H
#define C4_LOCATABLE_H

#include <iostream>
#include "../Lex/Token.h"
#include "Printable.h"


namespace C4
{
  namespace AST
  {
    ///
    struct Locatable : Printable
    {
      Locatable( Lex::Token const &tok ) : tok(tok) {}
      virtual ~Locatable() {}

      Lex::Token const tok;
    }; // end struct Locatable
  } // end namespace AST
} // end namespace C4

#endif
