

//===--- ASTNodeVisitor.h --------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the ASTNodeVisitor interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_ASTNODEVISITOR_H
#define C4_ASTNODEVISITOR_H

#include <iostream>

namespace C4
{
  namespace AST
  {
    
    struct BinaryExpression;
    struct Constant;
    struct Declaration;
    struct IllegalDeclaration;
    struct IllegalExpression;
    struct PostfixExpression;
    struct Statement;
    struct StringLiteral;
    struct Type;
    struct UnaryExpression;
    struct Variable;
    struct Expression;
    ///
    struct ASTNodeVisitor 
    {
      virtual void visit ( BinaryExpression & binaryExpression ) = 0;
      virtual void visit ( Constant & constant ) = 0;
      virtual void visit ( Declaration & declaration ) = 0;
      virtual void visit ( Expression & expression ) = 0;     
      virtual void visit ( IllegalDeclaration & illegalDeclaration ) = 0;      
      virtual void visit ( IllegalExpression & illegalExpression ) = 0;
      virtual void visit ( PostfixExpression & postfixExpression ) = 0;     
      virtual void visit ( Statement & statement ) = 0;      
      virtual void visit ( StringLiteral & stringLiteral ) = 0;
      virtual void visit ( Type & type ) = 0;
      virtual void visit ( UnaryExpression & unaryExpression ) = 0;
      virtual void visit ( Variable & variable ) = 0;
    }; 

  } // end namespace AST
} // end namespace C4

#endif
