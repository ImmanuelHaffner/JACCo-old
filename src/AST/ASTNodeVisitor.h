

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
#include "BinaryExpression.h"
#include "Constant.h"
#include "Declaration.h"
#include "Expression.h"
#include "IllegalDeclaration.h"
#include "IllegalExpression.h"
#include "PostfixExpression.h"
#include "Statement.h"
#include "StringLiteral.h"
#include "Type.h"
#include "UnaryExpression.h"
#include "Variable.h"

namespace C4
{
  namespace AST
  {
    ///
    struct ASTNodeVisitor 
    {
      virtual void visit ( BinaryExpression binaryExpression );
      virtual void visit ( Constant constant );
      virtual void visit ( Declaration declaration );
      virtual void visit ( Expression expression );     
      virtual void visit ( IllegalDeclaration illegalDeclaration );      
      virtual void visit ( IllegalExpression illegalExpression );
      virtual void visit ( PostfixExpression postfixExpression );     
      virtual void visit ( Statement statement );      
      virtual void visit ( StringLiteral stringLiteral);
      virtual void visit ( Type type );
      virtual void visit ( UnaryExpression unaryExpression );
      virtual void visit ( Variable variable );
      private:
      String printed;
    }; 

    std::ostream & operator<<( std::ostream &out,
        BinaryExpression const &expr );
  } // end namespace AST
} // end namespace C4

#endif
