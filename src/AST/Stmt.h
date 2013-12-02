//===--- Stmt.h ------------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the Abstract Syntax tree interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_STMT_H
#define C4_STMT_H

#include <iostream>

namespace C4
{
  namespace AST
  {
    ///
    struct Stmt
    {
      virtual ~Stmt() {}

      friend std::ostream & operator<<( std::ostream &out, Stmt const &stmt );
    }; // end struct Stmt

    std::ostream & operator<<( std::ostream &out, Stmt const &stmt );
  } // end namespace AST
} // end namespace C4

#endif
