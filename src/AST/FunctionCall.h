//===--- FunctionCall.h ---------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_FUNCTION_CALL_H
#define C4_FUNCTION_CALL_H

#include <iostream>
#include "PostfixExpr.h"
#include "../Lex/Token.h"

namespace C4
{
  namespace AST
  {
    ///
    struct FunctionCall : PostfixExpr
    {
      FunctionCall( Lex::Token const &tok, Expr const &expr
          /* TODO add argument-expr-list */ ) :
        PostfixExpr(tok), expr(expr) {}
      ~FunctionCall() {}

      friend std::ostream & operator<<( std::ostream &out,
          FunctionCall const &expr );

      Expr const &expr; 
      void print( Printer const p ) const;
    }; // end struct FunctionCall

    std::ostream & operator<<( std::ostream &out, FunctionCall const &expr );
  } // end namespace AST
} // end namespace C4

#endif
