//===--- SizeofExpr.h -----------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_SIZEOF_EXPR_H
#define C4_SIZEOF_EXPR_H

#include <iostream>
#include "UnaryExpr.h"
#include "../Lex/Token.h"

namespace C4
{
  namespace AST
  {
    ///
    struct SizeofExpr : UnaryExpr
    {
      SizeofExpr( Lex::Token const &tok, Expr const &expr ) :
        UnaryExpr(tok), expr(expr) {}
      ~SizeofExpr() {}

      friend std::ostream & operator<<( std::ostream &out,
          SizeofExpr const &expr );

      Expr const &expr; 
      void print( Printer const p ) const;
    }; // end struct UnaryExpr

    std::ostream & operator<<( std::ostream &out, SizeofExpr const &expr );
  } // end namespace AST
} // end namespace C4

#endif
