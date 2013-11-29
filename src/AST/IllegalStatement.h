//===--- IllegalStatement.h -----------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_ILLEGAL_STATEMENT_H
#define C4_ILLEGAL_STATEMENT_H

#include <iostream>
#include "Statement.h"


namespace C4
{
  namespace AST
  {
    ///
    struct IllegalStatement : Statement
    {
      IllegalStatement() {}
      virtual ~IllegalStatement() {}

      friend std::ostream & operator<<( std::ostream &out,
          IllegalStatement const &stmt );
    }; // end struct IllegalStatement

    std::ostream & operator<<( std::ostream &out,
        IllegalStatement const &stmt );
  } // end namespace AST
} // end namespace C4

#endif
