//===--- IllegalDeclaration.h ---------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the Abstract Syntax tree interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_ILLEGAL_DECLARATION_H
#define C4_ILLEGAL_DECLARATION_H

#include <iostream>
#include "Declaration.h"


namespace C4
{
  namespace AST
  {
    ///
    struct IllegalDeclaration : Declaration
    {
      virtual ~IllegalDeclaration() {}

      friend std::ostream & operator<<( std::ostream &out,
          IllegalDeclaration const &decl );
    };

    std::ostream & operator<<( std::ostream &out,
        IllegalDeclaration const &decl );
  } // end namespace AST
} // end namespace C4

#endif
