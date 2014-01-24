//===--- SemaTypeFactory.cc -----------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements a factory to construct sema types from the AST.
//
//===----------------------------------------------------------------------===//


#include "SemaTypeFactory.h"

#include "../Lex/Token.h"


using namespace C4;
using namespace Lex;
using namespace AST;
using namespace Sema;


bool FuncEqual::operator()( FuncType const * const t0,
    FuncType const * const t1 ) const
{
  // Compare return types.
  if ( t0->retType != t1->retType ) return false;

  // Compare the argument types.
  std::vector< Type const * > const &args0 = t0->argTypes;
  std::vector< Type const * > const &args1 = t1->argTypes;

  if ( args0.size() != args1.size() ) return false;

  // Compare argument types.
  for ( auto it0 = args0.begin(), it1 = args1.begin();
      it0 != args0.end() && it1 != args1.end();
      ++it0, ++it1 )
    if ( *it0 != *it1 ) return false;

  return true;
}


void TypeFactory::destroy()
{
  // clear the function type table
  for ( auto t : funcTable )
    delete t;
  funcTable.clear();

  // clear the pointer type table
  for ( auto t : ptrTable )
    delete t;
  ptrTable.clear();
}


// Initialize the function type table.
TypeFactory::FuncTable TypeFactory::funcTable(255);
TypeFactory::PtrTable TypeFactory::ptrTable(255);


// Initialize simple types.
VoidType const TypeFactory::VOID(HASH_Void);
BasicType const TypeFactory::CHAR(1 /* size */, HASH_Char);
BasicType const TypeFactory::INT(4 /* size */, HASH_Int);


Sema::Type const * TypeFactory::getVoid() { return &VOID; }

Sema::Type const * TypeFactory::getChar() { return &CHAR; }

Sema::Type const * TypeFactory::getInt() { return &INT; }

Sema::Type const * TypeFactory::getType( TypeSpecifier const * const typeSpec )
{
  switch ( typeSpec->tok.kind )
  {
    case TK::Void:
      return getVoid();

    case TK::Char:
      return getChar();

    case TK::Int:
      return getInt();

    case TK::Struct:
      return getType( static_cast< StructSpecifier const * >( typeSpec ) );

    default:
      return NULL;
  }
}

Sema::Type const * TypeFactory::getType( Decl const * decl )
{
  Sema::Type const * retType = getType( decl->typeSpec );

  if ( ! decl->declarator ) return retType;

  // Traverse all pointer declarators, and modify the return type.
  //
  // e.g.:  int * * p; => int -> int * -> int * *
  Declarator const * declarator = decl->declarator;
  while ( auto pd = dynamic_cast< PointerDeclarator const * >( declarator ) )
  {
    retType = getPtr( retType ); // get a pointer to the current return type
    declarator = pd->declarator;
  }

  if ( ! declarator ) return retType;

  if ( auto fd = dynamic_cast< FunctionDeclarator const * >( declarator ) )
  {
    return getType( retType, fd );
  }

  return NULL;
}

Sema::Type const * TypeFactory::getType( Type const * retType,
    FunctionDeclarator const * fd )
{
  std::vector< Type const * > args;

  // Iterate over all parameters.
  ParamList const * const params = fd->params;
  for ( auto it = params->begin(); it != params->end(); ++it )
    args.push_back( getType( *it ) );

  // Construct the function type.
  FuncType const * const ft = new FuncType( retType, args );

  // Internalize.
  auto it = funcTable.find( ft );
  if ( it != funcTable.end() )
  {
    delete ft;
    return *it;
  }
  funcTable.insert( ft );
  return ft;
}

Sema::Type const * TypeFactory::getType( AST::StructSpecifier const * const ss )
{
  std::unordered_map< Symbol, Type const * > args;

  // Iterate over all declarations.
  //
  // e.g.:  int x;
  //        int y;
  //        int z;
  StructDeclList const * decls = ss->structDecls;
  for ( auto decl = decls->begin(); decl != decls->end(); ++decl )
  {
    Type const * const type = getType( (*decl)->typeSpec );

    // Iterate over all declarators.
    //
    // e.g.:  int x, y, z;
    StructDeclaratorList const * const declarators = (*decl)->structDeclarators;
    for ( auto declarator = declarators->begin();
        declarator != declarators->end(); ++declarator )
    {
      // TODO iterate over the pointer declarators and get a modified type
      // e.g.:  int * * x;

      // TODO check the dynamic type of the declarator, and invoke the correct
      // getType method
      // e.g.:  int (*p)()

      // TODO insert a mapping from the identifier to the returned type
    }
  }

  return new StructType( args );
}

Sema::Type const * TypeFactory::getPtr( Type const * const innerType )
{
  PtrType const * const ptr = new PtrType( innerType );

  // Internalize.
  auto it = ptrTable.find( ptr );
  if ( it != ptrTable.end() )
  {
    delete ptr;
    return *it;
  }
  ptrTable.insert( ptr );
  return ptr;
}
