//===--- Type.h -----------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the Abstract Syntax tree interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_TYPE_H
#define C4_TYPE_H

#include <iostream>


namespace C4
{
  namespace AST
  {
    ///
    struct Type
    {
      virtual ~Type() {}

      friend std::ostream & operator<<( std::ostream &out, Type const &decl );
    }; // end struct Type

    std::ostream & operator<<( std::ostream &out, Type const &type );
  } // end namespace AST
} // end namespace C4

#endif
