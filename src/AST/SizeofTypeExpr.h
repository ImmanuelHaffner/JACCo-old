//===--- SizeofTypeExpr.h -----------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_SIZEOF_TYPE_EXPR_H
#define C4_SIZEOF_TYPE_EXPR_H

#include <iostream>
#include "UnaryExpr.h"
#include "Type.h"
#include "../Lex/Token.h"

namespace C4
{
  namespace AST
  {
    ///
    struct SizeofTypeExpr : UnaryExpr
    {
      SizeofTypeExpr( Lex::Token const &tok, Type const &type ) :
        UnaryExpr(tok), type(type) {}
      ~SizeofTypeExpr() {}

      friend std::ostream & operator<<( std::ostream &out,
          SizeofTypeExpr const &expr );

      Type const &type; 
      void print( Printer const p ) const;
    }; // end struct UnaryExpr

    std::ostream & operator<<( std::ostream &out, SizeofTypeExpr const &expr );
  } // end namespace AST
} // end namespace C4

#endif
