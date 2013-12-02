//===--- BinaryExpr.h -----------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_BINARY_EXPR_H
#define C4_BINARY_EXPR_H

#include <iostream>
#include "Expr.h"
#include "../Lex/Token.h"


namespace C4
{
  namespace AST
  {
    ///
    struct BinaryExpr : Expr
    {
      BinaryExpr( Lex::Token const &tok, Expr const &lhs, Expr const &rhs ) :
        Expr(tok), lhs(lhs), rhs(rhs) {}

      virtual ~BinaryExpr() {}
      void print( Printer const p ) const;
      friend std::ostream & operator<<( std::ostream &out,
          BinaryExpr const &expr );

      Expr const &lhs;
      Expr const &rhs;
    }; // end struct BinaryExpr

    std::ostream & operator<<( std::ostream &out,
        BinaryExpr const &expr );
  } // end namespace AST
} // end namespace C4

#endif
