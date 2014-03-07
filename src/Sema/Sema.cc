//===--- Sema.cc-----------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements the SemaObject interface.
//
//===----------------------------------------------------------------------===//


#include "Sema.h"

#include <iostream>
#include <sstream>
#include <cstring>
#include "../diagnostic.h"


using namespace C4;
using namespace Parse;
using namespace AST;
using namespace Sema;


static int parameterDepth = 0;
static std::vector< std::pair< Entity *,
  ParamDecl const * > > nameless_params;

#define ERROR( MSG ) \
{ std::ostringstream actual; \
  errorf( this->tok.pos, "%s", ( MSG ) ); }

#define ERROR_TOK( TOK, MSG ) \
{ std::ostringstream actual; \
  errorf( ( TOK ).pos, "%s", ( MSG ) ); }

Type const* toFuncPtrIfFunc(Type const *t);

bool isAssignmentCompatible(Type const *lhsType, Expr const *rhs)
{
  if(rhs->getEntity() == NULL) return false;
  Type const *rhsType = toFuncPtrIfFunc(rhs->getEntity()->type);

  return
    ( isStructType( lhsType ) && lhsType == rhsType ) ||
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

//===----------------------------------------------------------------------===//
//
//  Declaration
//
//===----------------------------------------------------------------------===//

Type const * Decl::analyze( Env &env ) const
{
  Sema::Type const * const type = typeSpec->analyze( env );

  if ( declarator )
  {
    Entity * const e = declarator->analyze( env, type );
    const_cast< Decl * >( this )->attachEntity( e );
  }
  else
  {
    Entity * const e = new Entity();
    e->type = type;
    const_cast< Decl * >( this )->attachEntity( e );
  }

  // We just have to return something...
  return NULL;
}

Sema::Type const * IllegalDecl::analyze( Env & ) const
{
  assert( false && "not implemented yet" );
  return TypeFactory::getVoid();
}

Entity * PointerDeclarator::analyze( Env &env,
    Sema::Type const * const t ) const
{
  if ( t == NULL )
    return NULL;
  if ( declarator )
    return declarator->analyze( env, TypeFactory::getPtr( t ) );

  // If the pointer declarator has no sub-declarator, we need a temporary entity
  // to ship the type information to the next upper declarator.
  Entity * const entity = env.insert( "$" );
  entity->type = TypeFactory::getPtr( t );
  return entity;
}

Entity * FunctionDeclarator::analyze( Env &env,
    Sema::Type const * const t ) const
{
  if ( parameterDepth == 0 )
    nameless_params.clear();

  env.pushScope();
  FuncType::params_t params = this->params->analyze( env );
  Scope * const paramScope = env.popScope();

  Sema::Type const * funType = TypeFactory::getFunc( t, params );
  if ( parameterDepth > 0 )
  {
    //functions are interpreted as function pointers
    funType = TypeFactory::getPtr( funType );
  }

  Entity * entity = NULL;

  if ( declarator )
    entity = declarator->analyze( env, funType );

  if ( ! parameterDepth )
  {
    //we don't need this scope otherwise
    env.pushScope( paramScope );
  }

  if ( entity ) return entity;

  Entity * entity2 = new Entity();
  entity2->type = funType;
  if ( ! parameterDepth )
    env.pushFunction( entity2 );
  return entity2;
}

Entity * Identifier::analyze( Env &env, Sema::Type const * const t )
  const
{
  if ( auto funcType = dynamic_cast< FuncType const * >( t ) )
  {
    // Check that the return type of the function is not a function type
    if ( dynamic_cast< FuncType const * const >( funcType->retType ) )
    {
      std::ostringstream oss;
      oss << this << "\nfunction must not return a function";
      ERROR( oss.str().c_str() );
    }

    // Try to map the identifier. Returns NULL, if the identifier is already
    // mapped.
    if ( Entity * const entity = env.insert( tok.sym ) )
    {
      entity->type = t;
      const_cast< Identifier * >( this )->attachEntity( entity );
      if ( parameterDepth == 0 )
        env.pushFunction( entity );

      return entity;
    }
    else
    {
      // If the identifier is already mapped, the function parameters may now
      // be specified or the function may be defined, or the declaration may be
      // given again (which is allowed).

      Entity * const entityOld = env.lookup( tok.sym );
      Type const * typeOld = entityOld->type;

      // Verify, that the identifier was mapped to a function type.
      if ( auto funcTypeOld = dynamic_cast< FuncType const * >( typeOld ) )
      {
        if ( parameterDepth == 0 )
          env.pushFunction( entityOld );

        // If the types differ, check whether the old type even had arguments.
        if ( funcTypeOld->params != funcType->params )
        {
          // If argument types haven been specified for this function type
          // already, give an error message.
          if ( funcTypeOld->params.size() > 0 )
          {
            auto other =
              static_cast< Identifier const * >( entityOld->getParent() );

            std::ostringstream oss;
            oss << "function '" << this->tok.sym <<
              "' has already been declared with other arguments at "
              << other->tok.pos;
            ERROR( oss.str().c_str() );
          }
          else
          {
            // The old function had no arguments specified, but the new one now
            // has. Therefore, we need to update the entity.
            entityOld->type = t;
          }
        }
      } // end if FuncType old type
      else {
        // If the old type is not a function type, then the identifier has
        // already been declarad as variable.

        auto other =
          static_cast< Identifier const * >( entityOld->getParent() );

        std::ostringstream oss;
        oss << "identifier '" << this->tok.sym.str() <<
          "' has already been declared as variable at "
          << other->tok.pos;
        ERROR( oss.str().c_str() );
      }
      const_cast< Identifier * >( this )->attachEntity( entityOld );
      return entityOld;
    }
  } // end if FuncType
  else
  {
    // If the type is not a function type, it must be a object type.
    ObjType const * const objType = static_cast< ObjType const * >( t );
    if ( t == NULL || ! objType->isComplete() )
    {
      std::ostringstream oss;
      oss << "cannot instantiate '" << this << "' with incomplete type";
      ERROR( oss.str().c_str() );
    }

    // Try to map the identifier. Returns NULL, if the identifier is already
    // mapped.
    if ( Entity * const e = env.insert( tok.sym ) )
    {
      e->type = t;
      const_cast< Identifier * >( this )->attachEntity( e );
      return e;
    }
    else
    {
      Entity * const origin = env.lookup( tok.sym );
      assert( origin->getParent() && "must have a parent" );

      auto idOld = static_cast< Identifier const * >( origin->getParent() );
      std::ostringstream oss;

      if ( dynamic_cast< FuncType const * >( origin->type ) )
      {
        oss << "identifier '" << this->tok.sym.str() <<
          "' has already been declared as function at " << idOld->tok.pos;
        ERROR( oss.str().c_str() );
      }
      else
      {
        oss << "identifier '" << this->tok.sym.str() <<
          "' has already been declared at " << idOld->tok.pos;
        ERROR( oss.str().c_str() );
      }

      const_cast< Identifier * >( this )->attachEntity( origin );
      return origin;
    }
  } // end else ObjType
}

Entity * IllegalDeclarator::analyze( Env &env, Sema::Type const * ) const
{
  // Create error entity with type void
  Entity * const entity = env.insert( "§" );
  entity->type = TypeFactory::getVoid();
  return entity;
}

void FunctionDef::analyze( Env &env ) const
{
  auto funDeclar = static_cast< FunctionDeclarator const * >( decl->declarator
      );

  // Check for missing parameter names
  // When parsing parameter declarations, the function name is still unknown, so
  // we have to check for the function below
  Entity * fe = env.popFunction();
  for ( std::pair< Entity *, ParamDecl const * > &it : nameless_params ) {
    if ( it.first  == env.topFunction() )
    {
      std::ostringstream oss;
      oss << "function '" << funDeclar->tok.sym.str() <<
        "' misses parameter name for " << it.second->tok.sym; //it
      ERROR_TOK( it.second->tok, oss.str().c_str() );
    }
  }
  env.pushFunction( fe );

  // get entity of the defined function
  Entity * e = decl->getEntity();

  // check if function was defined before
  if ( e->defined )
  {
    std::ostringstream oss;
    oss << "function '" << funDeclar->tok.sym.str() <<
      "' was already defined before at " << e->getParent(); //it
    ERROR_TOK( funDeclar->tok, oss.str().c_str() );
  }
  else
  {
    // mark function as defined
    e->defined = true;
  }

  // Check if all labels have corresponding gotos
  /*SymbolSet s = std::set_intersection( env.getLabelSymbols(),
    env.getGotoSymbols() );*/
  for ( auto target : *( env.getGotoTokens() ) )
  {
    if ( env.getLabelSymbols()->find( target->sym )
        == env.getLabelSymbols()->end() )
    {
      std::ostringstream oss;
      oss << "missing label '" << target->sym.str() << "'";
      ERROR_TOK( *target, oss.str().c_str() );
    }
  }
}

void StructDeclList::analyze( Env &env ) const
{
  for ( auto it : * this )
    it->analyze( env );
}

Sema::Type const * StructDecl::analyze( Env &env ) const {
  Sema::Type const * const t = typeSpec->analyze( env );
  if ( structDeclarators )
    structDeclarators->analyze( env, t );
  //we could do it better (for declarator lists), but probably won't need it
  return t;
}

void StructDeclaratorList::analyze( Env &env, Sema::Type const * const t ) const
{
  for ( auto it : *this )
    it->analyze( env, t );
}

Sema::Type const * ParamDecl::analyze( Env &env ) const
{
  Sema::Type const * t = typeSpec->analyze( env );
  size_t scopeSize1 = env.topScope()->getIdMap().size();
  if ( declarator )
  {
    t = declarator->analyze( env, t )->type;
  }
  size_t scopeSize2 = env.topScope()->getIdMap().size();
  if ( t != TypeFactory::getVoid() && parameterDepth == 1 && scopeSize1
      == scopeSize2 )
    nameless_params.push_back( std::make_pair( env.topFunction(), this ) );
  return t;
}

FuncType::params_t ParamList::analyze( Env &env ) const
{
  parameterDepth++;
  FuncType::params_t params;

  for ( auto it : * this )
    params.push_back( it->analyze( env ) );
  parameterDepth--;
  return params;
}

Sema::Type const * StructSpecifier::analyze( Env &env ) const
{
  Type *t = NULL;
  StructType::elements_t innerTypes;

  if ( structDecls )
  {
    // Construct type according to struct declarations
    env.pushScope();
    structDecls->analyze( env );
    Scope * const structScope = env.popScope();

    IdMap const &idMap = structScope->getIdMap();
    for ( auto it : idMap )
      innerTypes.insert( std::make_pair( it.first, it.second->type ) );

    t = TypeFactory::getStruct( innerTypes );
  }
  else
    t = TypeFactory::getStruct();

  if ( name )
  {
    auto st = const_cast< StructType * >(
        static_cast< StructType const * >( env.lookupType( name->sym ) ) );

    if ( ! structDecls ) {
      if ( ! st )
      {
        // First occurence of type with name 'name', create new incomplete
        // structure type
        env.insert( name->sym, t );
        return t;
      }
      // Known type, since we don't have a struct declaration list, we don't
      // overwrite it.
      return st;
    }

    // Try to insert new struct type
    if ( ! env.insert( name->sym, t ) )
    {
      // Type name already existing in current scope
      if ( st->isComplete() )
      {
        ERROR( "Cannot replace type information of already completed struct" );
      }
      else
        st->complete( innerTypes );

      return st;
    }
  }

  if ( t == NULL)
    // Illegal struct without name nor structdecls
    return TypeFactory::getVoid();

  // No name, so just return new struct type according to struct declaration
  // list
  return t;
}


Sema::Type const * TypeSpecifier::analyze( Env & ) const
{
  switch( tok.kind )
  {
    case Lex::TK::Void:
      return TypeFactory::getVoid();
    case Lex::TK::Int:
      return TypeFactory::getInt();
    case Lex::TK::Char:
      return TypeFactory::getChar();
    default:
      assert( false && "unknown type, should be unreachable" );
  }
  return NULL;
}

Sema::Type const * IllegalTypeSpecifier::analyze( Env & ) const
{
  return TypeFactory::getVoid();
}

void BreakStmt::analyze() const
{
  if ( ! Parser::isParsingIter() )
  {
    std::ostringstream oss;
    oss << "break statement outside body of iteration statement";
    ERROR( oss.str().c_str() );
  }
}

void ContinueStmt::analyze() const
{
  if ( ! Parser::isParsingIter() )
  {
    std::ostringstream oss;
    oss << "continue statement outside body of iteration statement";
    ERROR( oss.str().c_str() );
  }
}

void GotoStmt::analyze( Env &env ) const
{
  env.insertGoto( &( this->tok ) );
}

void LabelStmt::analyze( Env &env ) const
{
  Lex::Token const * lt = env.insertLabel( &( this->tok ) );
  if ( lt != &( this->tok ) )
  {
    std::ostringstream oss;
    oss << "label '" << this->tok.sym << "' already defined at " << lt->pos;
    ERROR( oss.str().c_str() );
  }
}

void ReturnStmt::analyze( Env &env ) const
{
  // Check if returned expression has function return type
  auto funcType = static_cast< FuncType const * >( env.topFunction()->type );

  if ( funcType->retType == TypeFactory::getVoid() )
  {
    if ( expr )
    {
      std::ostringstream oss;
      oss << "return may not have an expression";
      ERROR( oss.str().c_str() );
    }
    return;
  }

  if ( ! expr )
  {
    std::ostringstream oss;
    oss << "return needs an expression";
    ERROR( oss.str().c_str() );
    return;
  }

  if ( ! expr->getEntity() )
    return;

  if ( ! isAssignmentCompatible( funcType->retType, expr ) )
  {
    std::ostringstream oss;
    oss << "return value of type '" << expr->getEntity()->type <<
      "', should have type '" << funcType->retType << "'";
    ERROR( oss.str().c_str() );
  }
}

//TODO: Remove this macro
#define returnIfEitherNull(e1, e2) if((e1) == NULL || (e2) == NULL) return;
#define returnIfNull(e) if((e) == NULL) return;

Type const* toFuncPtrIfFunc(Type const *t)
{
  if(isFunctionType(t))
  {
    return TypeFactory::getPtr(t);
  }
  else
  {
    return t;
  }
}

void AssignmentExpr::analyze()
{
  returnIfEitherNull(lhs->getEntity(), rhs->getEntity());
  //§6.5.16.p2 - lhs must be modifiable lvalue.
  if( !lhs->isLvalue )
  {
    ERROR("Left hand side of assignment must be lvalue.");
  }
  Type const * lhsType = toFuncPtrIfFunc(lhs->getEntity()->type);
  if( ! isCompleteObjType(lhsType))
  {
    ERROR("Left hand side of assignment must be a complete type.");
  }

  //§6.5.16.p3 - assignment expression cannot be lvalue.
  this->isLvalue = false;

  if(!(isAssignmentCompatible(lhsType, rhs)))
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
    if(isObjType(entity->type))
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
  Type const *condType = toFuncPtrIfFunc(condEntity->type);
  returnIfNull(condEntity);

  //§6.5.15.p2 - The conditional expression shall have scalar type.
  if( ! isScalarType(condType))
  {
    ERROR("Predicate of conditional expression must of scalar type");
  }

  //§6.5.15.p3 - In restricted subset this amounts to the same checks
  // as assignment and additional void type check (§6.5.15.p3.pp3)
  Entity const *lhsEntity = lhs->getEntity();
  Entity const *rhsEntity = rhs->getEntity();
  returnIfEitherNull(lhsEntity, rhsEntity);
  Type const *lhsType = toFuncPtrIfFunc(lhsEntity->type);
  Type const *rhsType = toFuncPtrIfFunc(rhsEntity->type);
  Entity *e = new Entity();
  if(isArithmeticType(lhsType) && isArithmeticType(rhsType))
  {
    e->type = TypeFactory::getInt(); //§6.5.15.p5 : Approximate it to int
  }
  else if(isStructType(lhsType) && lhsType == rhsType)
  {
    e->type = lhsType;
  }
  else if(isVoidType(lhsType) && isVoidType(rhsType)) //§6.5.15.p5
  {
    e->type = TypeFactory::getVoid();
  }
  else if((isPointerType(lhsType) && isPointerType(rhsType) &&
        lhsType == rhsType))  //§6.5.15.p6
  {
    e->type = lhsType;
  }
  else if(isPointerType(lhsType) && isNullPointerConstant(rhs)) //§6.5.15.p6
  {
    e->type = lhsType;
  }
  else if(isPointerType(rhsType) && isNullPointerConstant(lhs)) //§6.5.15.p6
  {
    e->type = rhsType;
  }
  else if(isPointerType(lhsType) && isPointerType(rhsType) &&
      ( (isObjType(toPointerType(lhsType)->innerType) &&
         isVoidType(toPointerType(rhsType)->innerType)) ||
        (isObjType(toPointerType(rhsType)->innerType) &&
         isVoidType(toPointerType(lhsType)->innerType))))  //§6.5.15.p6
  {
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
  Type const *lhsType = toFuncPtrIfFunc(lhs->getEntity()->type);
  Type const *rhsType = toFuncPtrIfFunc(rhs->getEntity()->type);
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
  }
  else if((this->tok).kind == Lex::TK::Minus)
  {
    Entity *e = new Entity();
    if(isArithmeticType(lhsType) && isArithmeticType(rhsType)) //§6.5.6.p3.pp1 int?
    {
      e->type = TypeFactory::getInt();
    }
    else if(isPointerType(lhsType) && //§6.5.6.p3.pp2
        toPointerType(lhsType) == toPointerType(rhsType) &&
        toPointerType(lhsType)->isPointerToCompleteObj())
    {
      e->type = TypeFactory::getInt();
    }
    else if(isPointerType(lhsType) && //§6.5.6.p3.pp3
        toPointerType(lhsType)->isPointerToCompleteObj() &&
        isIntegerType(rhsType))
    {
      e->type = lhsType;
    }
    else
    {
      ERROR("Incompatible operands to minus.");
    }
    this->attachEntity(e);
  }
  else if((this->tok).kind == Lex::TK::Le)
  {
    Entity *e = new Entity();
    if((isRealType(lhsType) && isRealType(rhsType)) || //§6.5.8.p2.pp1
        (isPointerType(lhsType) && isPointerType(rhsType) &&//§6.5.8.p2.pp2 ?
         isObjType(toPointerType(lhsType)->innerType) &&
         isObjType(toPointerType(rhsType)->innerType) &&
         lhsType == rhsType))
    {
      e->type = TypeFactory::getInt();//§6.5.8.p6
    }
    else
    {
      ERROR("Expected real types or pointer to object types.")
    }
    this->attachEntity(e);
  }
  else if((this->tok).kind == Lex::TK::Eq || (this->tok).kind == Lex::TK::NE)
  {
    Entity *e = new Entity();
    //§6.5.9.p2
    if(isAssignmentCompatible(lhsType, rhs) ||
        isAssignmentCompatible(rhsType, lhs))
    {
      //§6.5.9.p3
      e->type = TypeFactory::getInt();
    }
    else
    {
      ERROR("Incompatible operands to == or !=.");
    }
    this->attachEntity(e);
  }
  else if((this->tok).kind == Lex::TK::LAnd || (this->tok).kind == Lex::TK::LOr)
  {
    Entity *e = new Entity();
    //§6.5.13.p2
    if(isScalarType(lhsType) && isScalarType(rhsType))
    {//§6.5.13.p3
      e->type = TypeFactory::getInt();
    }
    else
    {
      ERROR("Incompatible operands to == or !=.");
    }
    this->attachEntity(e);
  }
  this->isLvalue = false;
}

void UnaryOperation::analyze()
{
  Entity *childEntity = this->expr->getEntity();
  returnIfNull(childEntity);
  Entity *e = new Entity();
  if((this->tok).kind == Lex::TK::And)
  {
    Type const *childType = childEntity->type;
    if(isFunctionType(childType) ||
        (isUnaryOperation(expr) && expr->tok.kind == Lex::TK::Mul) ||
        (expr->isLvalue && isObjType(childType))) //§6.5.3.2.p1
    {//§6.5.3.2.p3
      e->type = TypeFactory::getPtr(childType);
    }
    else
    {
      ERROR("Incorrect operand for &.");
    }
    this->isLvalue = false;
  }
  else if((this->tok).kind == Lex::TK::Mul)
  {
    Type const *childType = toFuncPtrIfFunc(childEntity->type);
    if(isPointerType(childType)) //§6.5.3.2.p2
    {
      Type const *childInnerType = toPointerType(childType)->innerType;
      if(isFunctionType(childInnerType))
      {//§6.5.3.2.p4
        e->type = childInnerType;
        this->isLvalue = false;
      }
      else if(isObjType(toPointerType(childType)->innerType))
      {//§6.5.3.2.p4
        e->type = childInnerType;
        this->isLvalue = true;
      }
      else
      {//§6.5.3.2.p4
        ERROR("The operand of * is invalid pointer type.");
      }
    }
    else
    {
      ERROR("The operand of * must be pointer type.");
    }
  }
  else if((this->tok).kind == Lex::TK::Minus)
  {
    Type const *childType = toFuncPtrIfFunc(childEntity->type);
    if(isArithmeticType(childType)) //§6.5.3.3.p1
    {
      e->type = TypeFactory::getInt(); //§6.5.3.3.p3
    }
    else
    {
      ERROR("The operand of unary - must be arithmetic.");
    }
    this->isLvalue = false;
  }
  else if((this->tok).kind == Lex::TK::Not)
  {
    Type const *childType = toFuncPtrIfFunc(childEntity->type);
    if(isScalarType(childType)) //§6.5.3.3.p1
    {
      e->type = TypeFactory::getInt(); //§6.5.3.3.p5
    }
    else
    {
      ERROR("The operand of unary ! must be scalar.")
    }
  }
  this->attachEntity(e);
}

void SizeofExpr::analyze()
{
  Entity const *childEntity = expr->getEntity();
  returnIfNull(childEntity);
  Entity *e = new Entity();
  if( isFunctionType(childEntity->type) || //§6.5.3.4.p1
      (isObjType(childEntity->type) &&
       ! toObjType(childEntity->type)->isComplete()) )
  {
    ERROR("The operand of size of cannot be function type or incomplete object.");
  }
  e->type = TypeFactory::getInt(); //§6.5.3.4.p2
  this->attachEntity(e);
  this->isLvalue = false;
}

void SizeofTypeExpr::analyze() //§6.5.3.4
{
  Entity *e = new Entity();
  if( isFunctionType( typeName ) || //§6.5.3.4.p1
      ( isObjType( typeName ) &&
       ! toObjType( typeName )->isComplete() ) )
  {
    ERROR("The operand of size of cannot be function type or incomplete object.");
  }
  e->type = TypeFactory::getInt(); //§6.5.3.4.p2
  this->attachEntity(e);
  this->isLvalue = false;
}

void FunctionCall::analyze()
{
  Entity *exprEntity = fun->getEntity();
  returnIfNull(exprEntity);
  Type const *exprType = toFuncPtrIfFunc(exprEntity->type);

  //§6.5.2.2.p1
  if(isPointerType(exprType) &&
      isFunctionType(toPointerType(exprType)->innerType))
  {
    Entity *e = new Entity();
    Type const *innerType = toPointerType(exprType)->innerType;
    FuncType const *funcType = toFunctionType(innerType);
    FuncType::params_t voidParams;
    voidParams.push_back( TypeFactory::getVoid() );
    Type const *voidFuncType = TypeFactory::getFunc( funcType->retType,
        voidParams );

    if ( funcType->params.size() == 0 || ( funcType == voidFuncType &&
          ! this->args ) )
    { goto valid; }
    else if ( funcType->params.size() == toExprList(this->args)->size() )
    {
      auto iterActual = (toExprList(this->args))->begin();
      for(auto iterExpected = (funcType->params).begin();
          iterExpected != (funcType->params).end(); iterExpected++, iterActual++)
      {
        if(!isAssignmentCompatible(*iterExpected, *iterActual)) //§6.5.2.2.p2
        {
          std::ostringstream oss;
          oss << "Function call doesn't match the declared or inferred type"
            << " at " << iterExpected - (funcType->params).begin() + 1
            << " position starting 1.";
          ERROR( oss.str().c_str() );
        }
      }
    }
    else
    {
      ERROR("The number of arguments of function call doesn't match with declared/inferred type");
    }
valid:
    e->type = funcType->retType;   //§6.5.2.2.5 - The function call
    //expression has type of return type
    this->attachEntity(e);
  }
  else
  {
    ERROR("Expression denoting called function is not a pointer to a function")
  }

  //§6.8.6.4 - It seems that it cannot be an lvalue.
  this->isLvalue = false;
}

void DotExpr::analyze()
{
  Entity *exprEntity = expr->getEntity();
  returnIfNull(exprEntity);

  Type const *exprType = toFuncPtrIfFunc(exprEntity->type);
  //Entity *e = new Entity();

  //§6.5.2.3.p1
  if ( isStructType( exprType ) )
  {
    auto elements = toStructType( exprType )->elements;
    auto elem = elements.find( id.sym );
    if ( elem != elements.end() )
    {
      Entity * e = new Entity();
      e->type = elem->second; 
      attachEntity( e );
    }
    else
    {
      std::ostringstream oss;
      oss << "No member " << id.sym << " in struct with type " << exprType;
      ERROR( oss.str().c_str() );
    }
  }
  else
  {
    ERROR("The left side of . must be struct type.");
  }

  //§6.5.2.3.p3
  if(expr->isLvalue)
  {
    this->isLvalue = true;
  }
  else
  {
    this->isLvalue = false;
  }
}

void ArrowExpr::analyze()
{
  Entity *exprEntity = expr->getEntity();
  returnIfNull(exprEntity);
  Type const *exprType = toFuncPtrIfFunc(exprEntity->type);
  //Entity *e = new Entity();

  //§6.5.2.3.p2
  if( isPointerType( exprType ) &&
      isStructType( toPointerType( exprType )->innerType ) )
  {
    Type const * structType = toPointerType( exprType )->innerType; 
    auto elements = toStructType( structType )->elements;
    auto elem = elements.find( id.sym );
    if ( elem != elements.end() )
    {
      Entity * e = new Entity();
      e->type = elem->second; 
      attachEntity( e );
    }
    else
    {
      std::ostringstream oss;
      oss << "No member " << id.sym << " in struct with type " << structType;
      ERROR( oss.str().c_str() );
    }
  }
  else
  {
    ERROR("The left side of -> must be pointer to a struct.");
  }

  //§6.5.2.3.p4
  this->isLvalue = true;
}

void ExprList::analyze()
{
  auto lastElem = this->end() - 1;
  Entity *e = new Entity();
  if ( ( *lastElem )->getEntity() )
  {
    e->type = ( *lastElem )->getEntity()->type;
    this->attachEntity( e );
  }
}

void TypeName::analyze( Env &env )
{
  Sema::Type const * const type = typeSpec->analyze( env );

  if ( declarator )
  {
    parameterDepth = 1;
    Entity * const e = declarator->analyze( env, type );
    parameterDepth = 0;
    attachEntity( e );
  }
  else
  {
    Entity * const e = new Entity();
    e->type = type;
    attachEntity( e );
  }
}

void SubscriptExpr::analyze()
{
  returnIfEitherNull( this->expr->getEntity(), this->index->getEntity() );

  Type const * arrayType = this->expr->getEntity()->type;
  Type const * indexType = this->index->getEntity()->type;

  if ( ! isPointerType( arrayType ) ||
      ! isCompleteObjType( toPointerType( arrayType )->innerType ) )
  {
    std::ostringstream oss;
    oss << this->expr << " is not a pointer to a complete object type, but has "
      << "type " << arrayType;

    ERROR_TOK( this->expr->tok, oss.str().c_str() );
  }
  else
  {
    Entity * e = new Entity();
    e->type = toPointerType( arrayType )->innerType;
    attachEntity( e );
  }

  if ( ! isIntegerType( indexType ) )
  {
    std::ostringstream oss;
    oss << this->index << " is not of integer type, but of type " << indexType;
    ERROR_TOK( this->index->tok, oss.str().c_str() );
  }

  isLvalue = true;
}
