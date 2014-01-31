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

Sema::Type const * PointerDeclarator::analyze( Env &env, Sema::Type const * t ) const
{
  return declarator->analyze( env, TypeFactory::getPtr( t ) );
}

Sema::Type const * FunctionDeclarator::analyze( Env &env, Sema::Type const * t ) const
{
  std::vector<Sema::Type const *> paramTypes = params->analyze( env );
  Sema::Type const * funType = TypeFactory::getFunc( t, paramTypes );
  if ( declarator )
  {
    return declarator->analyze( env, funType );
  }
  return funType;
}

Sema::Type const * Identifier::analyze( Env &env, Sema::Type const * const t )
  const
{
  if ( Entity * const e = env.insert( tok.sym ) )
    e->type = t;
  else
  {
    std::ostringstream oss;
    oss << "identifier '" << this->tok.sym.str() <<
      "' has already been declared";
    ERROR( oss.str().c_str() );
  }
  return t;
}

Sema::Type const * IllegalDeclarator::analyze( Env &env, Sema::Type const * t ) const
{
  return NULL;
}

Sema::Type const * FunctionDef::analyze( Env &env ) const
{
  Sema::Type const * const t = typeSpec->analyze( env );
  if ( declarator )
    return declarator->analyze( env, t );
  return t;
}

void StructDeclList::analyze( Env &env ) const
{
  for ( auto &it : * this )
    it->analyze( env );
}

Sema::Type const * StructDecl::analyze( Env &env ) const
{
  Sema::Type const * const t = typeSpec->analyze( env );
  if ( structDeclarators )
    structDeclarators->analyze( env, t );
  //we could do it better, but probably won't need it
  return NULL;
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
    return declarator->analyze( env, t );
  return t;
}

std::vector< Sema::Type const * > ParamList::analyze( Env &env ) const
{
  std::vector< Sema::Type const * > paramTypes;
  for ( auto &it : * this )
    paramTypes.push_back( it->analyze( env ) );
  return paramTypes;
}

Sema::Type const * StructSpecifier::analyze( Env &env ) const
{
  Type const * oldType = NULL;
  if ( name )
  {
    oldType = env.lookupType( name->sym );
    if ( !structDecls )
     return oldType;
    if ( oldType != NULL )
    {
      //ERROR
      ;
      return oldType;
    }
  }

  //assume we have structDecls, otherwise we constructed a StructSpecifier
  //without name nor structDecls

  std::unordered_map< Symbol, Sema::Type const * > innerTypes;
  env.pushScope();
  structDecls->analyze( env );
  Scope structScope = env.popScope();
  for ( auto &it : structScope.getIdMap() )
    innerTypes.insert( std::make_pair( it.first, it.second->type ) );
  Sema::Type const * t = TypeFactory::getStruct( innerTypes );
  if ( name )
  {
    if ( oldType == NULL )
      if ( !env.insert ( name->sym, t ) )
        //TODO: ERROR
       1;
    else
      env.replaceType ( name->sym, t );
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
  {
    if ( t == NULL || t == TypeFactory::getVoid() )
      //TODO ERROR
      ;
    else
      return declarator->analyze( env, t );
  }
  return t;
}
