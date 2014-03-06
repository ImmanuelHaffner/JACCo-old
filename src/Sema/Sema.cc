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
  std::vector<Sema::Type const *> paramTypes = params->analyze( env );

  //if ( t == NULL )
  //{
    //if ( parameterDepth != 0 )
      //env.popScope();
    //return NULL;
  //}

  Scope * const paramScope = env.popScope();

  Sema::Type const * funType = TypeFactory::getFunc( t, paramTypes );
  if ( parameterDepth > 0 )
  {
    //functions are interpreted as function pointers
    funType = TypeFactory::getPtr( funType );
  }

  Entity * entity = NULL;

  if ( declarator )
    entity = declarator->analyze( env, funType );

  if ( parameterDepth == 0 )
  {
    //we don't need this scope otherwise
    env.pushScope( paramScope );
  }

  if ( entity ) return entity;

  Entity * entity2 = env.insert( "$" );
  entity2->type = funType;
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
      entity->attachParent( this );
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
        if ( funcTypeOld->argTypes != funcType->argTypes )
        {
          // If argument types haven been specified for this function type
          // already, give an error message.
          if ( funcTypeOld->argTypes.size() > 0 )
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
      e->attachParent( this );
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

  //check if entity has function type
  if ( ! dynamic_cast< FuncType const * >( e->type ) )
  {
    std::ostringstream oss;
    oss << "identifier '" << e->getParent() << "' is no function ";
    ERROR_TOK( funDeclar->tok, oss.str().c_str() );
  }

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

std::vector< Sema::Type const * > ParamList::analyze( Env &env ) const
{
  parameterDepth++;
  std::vector< Sema::Type const * > paramTypes;
  for ( auto &it : * this )
  {
    paramTypes.push_back( it->analyze( env ) );
  }
  parameterDepth--;
  return paramTypes;
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
    for ( auto &it : structScope->getIdMap() )
      innerTypes.push_back( std::make_pair( it.first, it.second->type ) );
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

  //TODO remove after completing sema
  if ( ! expr->getEntity() )
    return;

  //TODO uncomment after checkTypes is implemented properly
  /*if ( checkTypes( funcType->retType, expr->getEntity()->type )
    {
    std::ostringstream oss;
    oss << "return value of type '" << expr->getEntity()->type <<
    "', should have type '" << env.topFunction()->type << "'"; 
    ERROR( oss.str().c_str() );
    }*/
}
