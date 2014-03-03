//===--- TranslationUnit.h ------------------------------------------------===//
//
//  ~~~ The C4 Compiler ~~~
//
//  This file defines the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_TRNSL_UNIT_H
#define C4_TRNSL_UNIT_H

#include <iostream>
#include <vector>
#include "List.h"


namespace C4
{
  /* Forward declarations */
  namespace CodeGen
  {
    struct CodeGenFunction;
  }

  namespace AST
  {
    /* Forward declarations */
    struct ExtDecl;

    /// Translation Unit
    struct TranslationUnit : List< ExtDecl >
    {
      TranslationUnit() {}

      TranslationUnit( std::vector< ExtDecl const * > extDecls ) :
        List(extDecls)
      {}

      ~TranslationUnit() {}

      void print( Printer const p ) const;
      void emit( CodeGen::CodeGenFunction &CGF ) const;
    }; // end struct TranslationUnit
  } // end namespace AST
} // end namespace C4

#endif
