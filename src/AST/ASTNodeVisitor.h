

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
      virtual void visit ( BinaryExpression & binaryExpression );
      virtual void visit ( Constant & constant );
      virtual void visit ( Declaration & declaration );
      virtual void visit ( Expression & expression );     
      virtual void visit ( IllegalDeclaration & illegalDeclaration );      
      virtual void visit ( IllegalExpression & illegalExpression );
      virtual void visit ( PostfixExpression & postfixExpression );     
      virtual void visit ( Statement & statement );      
      virtual void visit ( StringLiteral & stringLiteral );
      virtual void visit ( Type & type );
      virtual void visit ( UnaryExpression & unaryExpression );
      virtual void visit ( Variable & variable );
    }; 

  } // end namespace AST
} // end namespace C4

#endif
