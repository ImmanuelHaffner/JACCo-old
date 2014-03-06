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
#include "TypeHelper.h"

using namespace C4;
using namespace AST;
using namespace Sema;


#define ERROR( MSG ) \
{ std::ostringstream actual; \
  errorf( this->tok.pos, "%s", ( MSG ) ); }

//TODO: Remove this macro
#define returnIfEitherNull(e1, e2) if((e1) == NULL || (e2) == NULL) return;
#define returnIfNull(e) if((e) == NULL) return;

bool isAssignmentCompatible(Expr const *lhs, Expr const *rhs)
{
  if(lhs->getEntity() == NULL || rhs->getEntity() == NULL) return false;

  Type const *lhsType = lhs->getEntity()->type;
  Type const *rhsType = rhs->getEntity()->type;

  return
  (isArithmeticType(lhsType) && isArithmeticType(rhsType)) || //§6.5.16.1.p1.pp1

  (isPointerType(lhsType) && isPointerType(rhsType) &&
      lhsType == rhsType) || //§6.5.16.1.p1.pp3

  (isPointerType(lhsType) && isPointerType(rhsType) &&
      ( (isObjType(toPointerType(lhsType)->innerType) &&
          isVoidType(toPointerType(rhsType)->innerType)) ||
        (isObjType(toPointerType(rhsType)->innerType) &&
          isVoidType(toPointerType(lhsType)->innerType)))) || //§6.5.16.1.p1.pp4

  (isPointerType(lhsType) && isNullPointerConstant(rhs)) //§6.5.16.1.p1.pp5
  ;
}

void AssignmentExpr::analyze()
{
  returnIfEitherNull(lhs->getEntity(), rhs->getEntity());
  //§6.5.16.p2 - lhs must be modifiable lvalue.
  if( !lhs->isLvalue )
  {
    ERROR("Left hand side of assignment must be lvalue.");
  }
  Type const * lhsType = lhs->getEntity()->type;
  if(isCompleteObjType(lhsType))
  {
    ERROR("Left hand side of assignment must be a complete type.");
  }

  //§6.5.16.p3 - assignment expression cannot be lvalue.
  this->isLvalue = false;

  if(!(isAssignmentCompatible(lhs, rhs)))
  {
    ERROR("Incompatible operands of assignment.");
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
  returnIfNull(condEntity);

  //§6.5.15.p2 - The conditional expression shall have scalar type.
  if(isScalarType(condEntity->type))
  {
    ERROR("Predicate of conditional expression must of scalar type");
  }
  
  //§6.5.15.p3 - In restricted subset this amounts to the same checks
  // as assignment and additional void type check (§6.5.15.p3.pp3)
  Entity const *lhsEntity = lhs->getEntity();
  Entity const *rhsEntity = rhs->getEntity();
  returnIfEitherNull(lhsEntity, rhsEntity);
  Entity *e = new Entity();
  if(isArithmeticType(lhsEntity->type) && isArithmeticType(rhsEntity->type))
  {//§6.5.15.p5 : Approximate it to int
    e->type = TypeFactory::getInt();
  }
  else if(isVoidType(lhsEntity->type) && isVoidType(rhsEntity->type))
  {//§6.5.15.p5
    e->type = TypeFactory::getVoid();
  }
  else if((isPointerType(lhsEntity->type) && isPointerType(rhsEntity->type) &&
      lhsEntity->type == rhsEntity->type))
  {//§6.5.15.p6
    e->type = lhsEntity->type;
  }
  else if(isPointerType(lhsEntity->type) && isNullPointerConstant(rhs))
  {//§6.5.15.p6
    e->type = lhsEntity->type;
  }
  else if(isPointerType(rhsEntity->type) && isNullPointerConstant(lhs))
  {//§6.5.15.p6
    e->type = rhsEntity->type;
  }
  else if(isPointerType(lhsEntity->type) && isPointerType(rhsEntity->type) &&
      ( (isObjType(toPointerType(lhsEntity->type)->innerType) &&
          isVoidType(toPointerType(rhsEntity->type)->innerType)) ||
        (isObjType(toPointerType(rhsEntity->type)->innerType) &&
          isVoidType(toPointerType(lhsEntity->type)->innerType))))
  {//§6.5.15.p6
    e->type = TypeFactory::getVoid();
  }
  else
  {
    ERROR("Invalid consequent and antecedent of conditional expression.");
  }
  this->attachEntity(e);

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
  else if((this->tok).kind == Lex::TK::Plus)
  {
    bool isPointer = false;
    //§6.5.6.p2
    if(!(isArithmeticType(lhsType) && isArithmeticType(rhsType)))
    {
      if(!( (isPointerType(lhsType)
             && toPointerType(lhsType)->isPointerToCompleteObj()
             && isIntegerType(rhsType)) ||
            (isPointerType(rhsType)
             && toPointerType(rhsType)->isPointerToCompleteObj()
             && isIntegerType(lhsType)) ))
      {
        ERROR("Pointer + Integer expected or integer operands expected.");
      }
      else
      {
        isPointer = true;
      }
    }

    //§6.5.6.p4
    Entity * const resultEntity = new Entity();
    if(isPointer)
    {
      if(isPointerType(lhsType))
      {
        resultEntity->type = lhsType;
      }
      else
      {
        resultEntity->type = rhsType;
      }
    }
    else
    {
      resultEntity->type = TypeFactory::getInt();
    }
    this->attachEntity(resultEntity);

    //? Assuming no lvalue
    this->isLvalue = false;
  }
  else if((this->tok).kind == Lex::TK::Minus)
  {
    Entity *e = new Entity();
    if(isArithmeticType(lhsType) && isArithmeticType(rhsType))
    {//§6.5.6.p3.pp1 int?
      e->type = TypeFactory::getInt();
    }
    else if(isPointerType(lhsType) &&
            toPointerType(lhsType) == toPointerType(rhsType) &&
            toPointerType(lhsType)->isPointerToCompleteObj())
    {//§6.5.6.p3.pp2
      e->type = TypeFactory::getInt();
    }
    else if(isPointerType(lhsType) &&
            toPointerType(lhsType)->isPointerToCompleteObj() &&
            isIntegerType(rhsType))
    {//§6.5.6.p3.pp3
      e->type = lhsType;
    }
    else
    {
      ERROR("Incompatible operands to minus.");
    }
    this->attachEntity(e);
  }
}

void FunctionCall::analyze()
{
  //§6.5.2.2.5 - The function call expression has type of return type

  //§6.8.6.4 - It seems that it cannot be an lvalue.
}

