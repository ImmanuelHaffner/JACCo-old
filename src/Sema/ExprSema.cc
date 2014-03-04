//===--- Sema.cc-----------------------------------------------------------===//
//
//  ~~~ The C4 Compiler ~~~
//
//  This file implements the SemaObject interface.
//
//===----------------------------------------------------------------------===//


#include "Sema.h"

#include <iostream>
#include <sstream>
#include <cstring>
#include <string.h>
#include "../diagnostic.h"
#include "../Support/EntityHolder.h"
#include "../AST/ASTFactory.h"

using namespace C4;
using namespace AST;
using namespace Sema;


#define ERROR( MSG ) \
{ std::ostringstream actual; \
  errorf( this->tok.pos, "%s", ( MSG ) ); }

//TODO: Remove this macro
#define returnIfEitherNull(e1, e2) if((e1) == NULL || (e2) == NULL) return;

bool checkTypes(Type const  *lhs, Type const *rhs)
{
  bool isCorrect = false;
  if( lhs != rhs )
  {
    auto pointerType = dynamic_cast< PtrType const * >( lhs );
    auto rhsExpr = dynamic_cast< Constant const * >( rhs );
    if( pointerType != NULL && rhsExpr != NULL)
    {
      isCorrect = (strcmp(rhsExpr->tok.sym.str(), "0") == 0);
    }
    else
    {
      isCorrect = false;
    }
  }
  else
  {
    isCorrect = true;
  }
  return isCorrect;
}

void AssignmentExpr::analyze()
{
  //§6.5.16.p2 - lhs must be modifiable lvalue.
  if( !lhs->isLvalue )
  {
    ERROR("Left hand side of assignment must be lvalue.");
  }
  Type const * lhsType = lhs->getEntity()->type;
  auto ot = dynamic_cast< ObjType const * >( lhsType );
  if( ot != NULL && !ot->isComplete() )
  {
    ERROR("Left hand side of assignment must be a complete type.");
  }

  //§6.5.16.p3 - assignment expression cannot be lvalue.
  this->isLvalue = false;

  //§6.5.16.1.p1.pp5 - either assignment between same types ( 'char' and 'int'
  //are same 'Basic Type') or assignment of constant 0 to pointer type.
  Type const * rhsType = rhs->getEntity()->type;
  if(!checkTypes(lhsType, rhsType))
  {
    ERROR("Incompatible operands of assignment. "
          "Must be same or assignment of 0 to a pointer type");
  }

  //§6.5.16.p3 - The type of assignment is type of lhs
  Entity *entity = new Entity();
  entity->type = lhs->getEntity()->type;
  this->attachEntity(entity);
}

void Variable::analyze(Env &env)
{
  //§6.5.1.2 - Must be declared in environment.
  Entity *entity = env.lookup(tok.sym);
  if(entity == NULL || entity->type == NULL)
  {
    ERROR("Use of undeclared variable.");
  }
  else
  {
    this->attachEntity(entity);
    //§6.5.1.2 - An identifier is lvalue if not a function designator.
    Type const *objectType = dynamic_cast<ObjType const *>(entity->type);
    if(objectType != NULL)
    {
      this->isLvalue = true;
    }
  }
}

void Constant::analyze()
{
  //§6.4.4 - In our case both character and integer constant are of type int.
  Entity *entity = new Entity();
  entity->type = TypeFactory::getInt();
  this->attachEntity(entity);
  //§6.5.1.3
  this->isLvalue = false;
}

void StringLiteral::analyze()
{
  //§6.4.5 - The type of string literal is array type. Since we do not have
  //arrays in our restricted subset, we model it by char*.
  Type const *ch = TypeFactory::getChar();
  Entity *entity = new Entity();
  entity->type = TypeFactory::getPtr(ch);
  this->attachEntity(entity);
  //§6.5.1.4 - String literal is lvalue.
  this->isLvalue = true;
}

void ConditionalExpr::analyze()
{
  Entity *condEntity = cond->getEntity();
  //TODO: Remove null check
  //§6.5.15.p2 - The conditional expression shall have scalar type.
  if(condEntity == NULL || 
     dynamic_cast<ScalarType const *>(condEntity->type) == NULL)
  {
    ERROR("Predicate of conditional expression must of scalar type");
  }
  
  //§6.5.15.p3 - For the restricted subset both lhs, rhs must have same type
  // or one must be a pointer and other a null pointer constant.
  Entity * const lhsEntity = lhs->getEntity();
  Entity * const rhsEntity = rhs->getEntity();
  //TODO:: Remove null check 
  if(lhsEntity != NULL && rhsEntity != NULL)
  {
    if(!checkTypes(lhsEntity->type, rhsEntity->type) &&
       !checkTypes(rhsEntity->type, lhsEntity->type))
    {
      ERROR("Ant and Cons of condition exp are incompatible.");
    }
  }
  else
  {
    return;
  }

  //§6.5.15.p6 - For the restricted subset, type of conditional expression
  // is same as lhs and rhs. When one of them is null pointer constant then
  // it is of other type.
  if(dynamic_cast<Constant const *>(lhsEntity->type) != NULL)
  {
    this->attachEntity(lhsEntity);
  }
  else
  {
    this->attachEntity(rhsEntity);
  }

  //§6.5.15.p4 - A conditional expression does not yield an lvalue.
  this->isLvalue = false;
}
  
void BinaryExpr::analyze()
{
  returnIfEitherNull(lhs->getEntity(), rhs->getEntity());
  Type const *lhsType = lhs->getEntity()->type;
  Type const *rhsType = rhs->getEntity()->type;
  if((this->tok).kind == Lex::TK::Mul)
  {
    //§6.5.5.p2 - The operands shall have arithmetic type.
    if(dynamic_cast<ArithmeticType const *>(lhsType) == NULL ||
       dynamic_cast<ArithmeticType const *>(rhsType) == NULL)
    {
      ERROR("The operands of * must be arithmetic.");
    }
    
    //§6.5.5.p4 ? Make the resulting type as int our case.
    Entity * const intEntity = new Entity();
    intEntity->type = TypeFactory::getInt();
    this->attachEntity(intEntity);

    //? Assuming no lvalue.
    this->isLvalue = false;
  }
}

void FunctionCall::analyze()
{
  //§6.5.2.2.5 - The function call expression has type of return type

  //§6.8.6.4 - It seems that it cannot be an lvalue.
}

