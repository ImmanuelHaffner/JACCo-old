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
using namespace AST;
using namespace Sema;

static int parameterDepth = 0;

#define ERROR( MSG ) \
{ std::ostringstream actual; \
  errorf( this->tok.pos, "%s", ( MSG ) ); }


//===----------------------------------------------------------------------===//
//
//  Declaration
//
//===----------------------------------------------------------------------===//

Sema::Type const * IllegalDecl::analyze( Env &env ) const
{
  return NULL;
}

Sema::Type const * PointerDeclarator::analyze( Env &env,
		Sema::Type const * const t ) const
{
  if ( declarator )
    return declarator->analyze( env, TypeFactory::getPtr( t ) );
  return TypeFactory::getPtr( t );
}

Sema::Type const * FunctionDeclarator::analyze( Env &env,
		Sema::Type const * const t ) const
{
  env.pushScope();
  std::vector<Sema::Type const *> paramTypes = params->analyze( env );
  Scope * const paramScope = env.popScope();
  Sema::Type const * funType = TypeFactory::getFunc( t, paramTypes );
  if ( parameterDepth > 0 )
  {
    //functions are interpreted as function pointers
    funType = TypeFactory::getPtr( funType );
  }
  if ( declarator )
    funType = declarator->analyze( env, funType );
  if ( parameterDepth == 0 )
  {
    //we don't need this scope otherwise
    env.pushScope( paramScope );
  }
  return funType;
}

Sema::Type const * Identifier::analyze( Env &env, Sema::Type const * const t )
  const
{
  if ( auto funcType = dynamic_cast< FuncType const * >( t ) )
  {
    if ( dynamic_cast< FuncType const * const >( funcType->retType ) )
    {
      std::ostringstream oss;
      oss << this << "\nfunction may not be declared with function return type "
				<< funcType->retType;
      ERROR( oss.str().c_str() );
    }
    if ( Entity * const e = env.insert( tok.sym ) )
      e->type = t;
    else
    {
      Entity * const oe = env.lookup( tok.sym );
      Type const * ot = oe->type;
      if ( auto oft = dynamic_cast< FuncType const * >( ot ) )
      {
        if ( oft->argTypes.size() > 0 )
        {
          if ( oft->argTypes != funcType->argTypes )
          {
            std::ostringstream oss;
            oss << "function '" << this->tok.sym.str() <<
              "' has been declared with other arguments before";
            ERROR( oss.str().c_str() );
          }
        }
        else {
          if ( funcType->argTypes.size() > 0 )
          {
            oe->type = t;
          }
        }
      }
      else {
        std::ostringstream oss;
        oss << "identifier '" << this->tok.sym.str() <<
          "' has already been declared";
        ERROR( oss.str().c_str() );
      }
    }
  }
  else
  {
    if ( t == NULL || t == TypeFactory::getVoid() )
    {
      std::ostringstream oss;
      oss << "Cannot instantiate " << this <<
        " with incomplete type";
      ERROR( oss.str().c_str() );
    }
    if ( Entity * const e = env.insert( tok.sym ) )
      e->type = t;
    else
    {
      std::ostringstream oss;
      oss << "identifier '" << this->tok.sym.str() <<
        "' has already been declared";
      ERROR( oss.str().c_str() );
    }
  }
  return t;
}

Sema::Type const * IllegalDeclarator::analyze( Env &env, Sema::Type const * t ) const
{
  return NULL;
}

Sema::Type const * FunctionDef::analyze( Env &env ) const
{
  return NULL;
}

void StructDeclList::analyze( Env &env ) const
{
  for ( auto &it : * this )
  {
    //Push parameter scope in case of function arguments
    env.pushScope();
    it->analyze( env );
    env.popScope();
  }
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
  for ( auto &it : *this )
    it->analyze( env, t );
}

Sema::Type const * ParamDecl::analyze( Env &env ) const
{
  Sema::Type const * t = typeSpec->analyze( env );
  if ( declarator )
  {
    t = declarator->analyze( env, t );
  }
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
  Type * t = NULL;
  StructType::elements_t innerTypes;
  if ( structDecls )
  {
    env.pushScope();
    structDecls->analyze( env );
    Scope * const structScope = env.popScope();
    for ( auto &it : structScope->getIdMap() )
      innerTypes.insert( std::make_pair( it.first, it.second->type ) );
    t = TypeFactory::getStruct( innerTypes );
  }
  else
    t = TypeFactory::getStruct();
  if ( name )
  {
    if ( !env.insert( name->sym, t ) )
    {
      auto st = const_cast< StructType * >(
					static_cast< StructType const * >( env.lookupType( name->sym ) ) );
      if ( structDecls )
      {
        if ( st->isComplete() )
        {
          ERROR( "Cannot replace type information of already completed struct" );
        }
        else
          st->complete( innerTypes );
      }
      return st;
    }
  }
  return t;
}


Sema::Type const * TypeSpecifier::analyze( Env &env ) const
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
      return NULL;
  }
}

Sema::Type const * IllegalTypeSpecifier::analyze( Env &env ) const
{
  return NULL;
}

Sema::Type const * Decl::analyze( Env &env ) const
{
  Sema::Type const * const t = typeSpec->analyze( env );
  if ( declarator )
    return declarator->analyze( env, t );
  return t;
}
