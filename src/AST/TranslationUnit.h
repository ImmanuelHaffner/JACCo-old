//===--- TranslationUnit.h ------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_TRNSL_UNIT_H
#define C4_TRNSL_UNIT_H

#include <iostream>
#include <vector>
#include "Printable.h"


namespace C4
{
  namespace AST
  {
    // Forward Declaration
    struct ExtDecl;

    /// Translation Unit
    struct TranslationUnit : Printable
    {
      ~TranslationUnit() {}

      inline void append( ExtDecl const * const extDecl )
      {
        extDecls.push_back( extDecl );
      }

      TranslationUnit & operator+=( ExtDecl const * const extDecl )
      {
        this->append( extDecl );
        return *this;
      }

      private:
      std::vector< ExtDecl const * > extDecls;
    }; // end struct TranslationUnit
  } // end namespace AST
} // end namespace C4

#endif
