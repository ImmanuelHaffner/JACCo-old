//===--- ASTVisitor.h -----------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the ASTNodeVisitor interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_AST_VISITOR_H
#define C4_AST_VISITOR_H

#include "AST.h"


namespace C4
{
  namespace AST
  {
    ///
    struct ASTVisitor 
    {
      //
      //  Expressions
      //

      virtual void visit( Expression &expr ) = 0;     
      virtual void visit( IllegalExpr &expr ) = 0;
      virtual void visit( Variable &expr ) = 0;
      virtual void visit( Constant &expr ) = 0;
      virtual void visit( StringLiteral &expr )
      virtual void visit( BinaryExpr &expr ) = 0;
      virtual void visit( PostfixExpr &expr ) = 0;     
      virtual void visit( UnaryExpr &expr ) = 0;


      //
      //  Statement
      //

      virtual void visit( Statement &stmt ) = 0;      

      //
      //  Declaration
      //

      virtual void visit( Declaration &decl ) = 0;
      virtual void visit( IllegalDeclaration &decl ) = 0;      


      //
      //  Type
      //

      virtual void visit( Type &type ) = 0;

    }; // end struct ASTVisitor
  } // end namespace AST
} // end namespace C4

#endif
