//===--- IllegalStmt.h -----------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_ILLEGAL_STMT_H
#define C4_ILLEGAL_STMT_H

#include <iostream>
#include "Stmt.h"


namespace C4
{
  namespace AST
  {
    ///
    struct IllegalStmt : Stmt
    {
      IllegalStmt() {}
      virtual ~IllegalStmt() {}

      friend std::ostream & operator<<( std::ostream &out,
          IllegalStmt const &stmt );
    }; // end struct IllegalStmt

    std::ostream & operator<<( std::ostream &out, IllegalStmt const &stmt );
  } // end namespace AST
} // end namespace C4

#endif
