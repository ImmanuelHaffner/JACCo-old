//===--- Declaration.h ----------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the Abstract Syntax tree interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_DECLARATION_H
#define C4_DECLARATION_H

#include <iostream>

namespace C4
{
  namespace AST
  {
    ///
    struct Declaration
    {
      virtual ~Declaration() {}

      friend std::ostream & operator<<( std::ostream &out,
          Declaration const &decl );
    };

    std::ostream & operator<<( std::ostream &out, Declaration const &decl );
  } // end namespace AST
} // end namespace C4

#endif
