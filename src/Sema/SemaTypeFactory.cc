//===--- SemaTypeFactory.cc -----------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements a factory to construct sema types from the AST.
//
//===----------------------------------------------------------------------===//


#include "SemaTypeFactory.h"


using namespace C4;
using namespace Sema;


VoidType const TypeFactory::VOID;
BasicType const TypeFactory::CHAR(1);
BasicType const TypeFactory::INT(4);

TypeFactory::TypeFactory()
{
}

Type const * TypeFactory::getVoid() const { return &VOID; }

Type const * TypeFactory::getChar() const { return &CHAR; }

Type const * TypeFactory::getInt() const { return &INT; }

Type const * TypeFactory::getPtr( Type const * const )
{
  // TODO implement
  return NULL;
}
