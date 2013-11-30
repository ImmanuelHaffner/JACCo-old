//===--- SignatureExpr.h --------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_SIGNATURE_EXPR_H
#define C4_SIGNATURE_EXPR_H

#include <iostream>
#include "PostfixExpr.h"
#include "../Lex/Token.h"

namespace C4
{
  namespace AST
  {
    ///
    struct SignatureExpr : PostfixExpr
    {
      SignatureExpr( Lex::Token const &tok, Expr const &expr
          /* TODO add argument-expr-list */ ) :
        PostfixExpr(tok), expr(expr) {}
      ~SignatureExpr() {}

      friend std::ostream & operator<<( std::ostream &out,
          SignatureExpr const &expr );

      Expr const &expr;
    }; // end struct SignatureExpr

    std::ostream & operator<<( std::ostream &out, SignatureExpr const &expr );
  } // end namespace AST
} // end namespace C4

#endif
