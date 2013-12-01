//===--- IllegalType.h ----------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_ILLEGAL_TYPE_H
#define C4_ILLEGAL_TYPE_H

#include <iostream>
#include "Type.h"


namespace C4
{
  namespace AST
  {
    ///
    struct IllegalType : Type
    {
      IllegalType( Lex::Token const &tok ) : Type(tok) {}
      virtual ~IllegalType() {}

      friend std::ostream & operator<<( std::ostream &out,
          IllegalType const &expr );
    }; // end struct IllegalType

    std::ostream & operator<<( std::ostream &out, IllegalType const &expr );
  } // end namespace AST
} // end namespace C4

#endif
