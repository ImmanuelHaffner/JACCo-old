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
    /// Statement
    struct Stmt
    {
      virtual ~Stmt() {}

      friend std::ostream & operator<<( std::ostream &out, Stmt const &stmt );
    }; // end struct Stmt
    std::ostream & operator<<( std::ostream &out, Stmt const &stmt );

    /// Illegal Statement
    struct IllegalStmt : Stmt
    {
      IllegalStmt() {}
      virtual ~IllegalStmt() {}

      friend std::ostream & operator<<( std::ostream &out,
          IllegalStmt const &stmt );
    }; // end struct IllegalStmt
    std::ostream & operator<<( std::ostream &out, IllegalStmt const &stmt );

    /// If Statement
    struct IfStmt : Stmt
    {
      IfStmt() {}
      virtual ~IfStmt() {}

      friend std::ostream & operator<<( std::ostream &out,
          IfStmt const &stmt );
    }; // end struct IfStmt
    std::ostream & operator<<( std::ostream &out, IfStmt const &stmt );
  } // end namespace AST
} // end namespace C4

#endif
