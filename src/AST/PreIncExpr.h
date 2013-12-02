//===--- PreIncExpr.h -----------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_PRE_INC_EXPR_H
#define C4_PRE_INC_EXPR_H

#include <iostream>
#include "UnaryExpr.h"
#include "../Lex/Token.h"

namespace C4
{
  namespace AST
  {
    ///
    struct PreIncExpr : UnaryExpr
    {
      PreIncExpr( Lex::Token const &tok, Expr const &expr ) :
        UnaryExpr(tok), expr(expr) {}
      ~PreIncExpr() {}

      friend std::ostream & operator<<( std::ostream &out,
          PreIncExpr const &expr );

      Expr const &expr; 
      void print( Printer const ) const;
    }; // end struct PreIncExpr

    std::ostream & operator<<( std::ostream &out, PreIncExpr const &expr );
  } // end namespace AST
} // end namespace C4

#endif
