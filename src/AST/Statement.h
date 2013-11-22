//===--- Statement.h ------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the Abstract Syntax tree interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_STATEMENT_H
#define C4_STATEMENT_H

#include <iostream>

namespace C4
{
  namespace AST
  {
    ///
    struct Statement
    {
      virtual ~Statement() {}

      friend std::ostream & operator<<( std::ostream &out,
          Statement const &stmt );
    }; // end struct Statement

    std::ostream & operator<<( std::ostream &out, Statement const &stmt );
  } // end namespace AST
} // end namespace C4

#endif
