//===--- Type.cc ----------------------------------------------------------===//
//
//  ~~~ The C4 Compiler ~~~
//
//  This file implements the semantic types.
//
//===----------------------------------------------------------------------===//


#include "Type.h"


using namespace C4;
using namespace Sema;


std::ostream & Sema::operator<<( std::ostream &out, Type const &type )
{
  type.print( out );
  return out;
}

std::ostream & Sema::operator<<( std::ostream &out,
    Type const * const type )
{
  type->print( out );
  return out;
}

void Type::dump() const
{
  this->print( std::cout );
  std::cout << std::endl;
}

void FuncType::print( std::ostream &out ) const
{
  this->retType->print( out );
  out << " (";

  auto it = params.begin();
  if ( it != params.end() )
  {
    (*it)->print( out );
    ++it;
    for ( ; it != params.end(); ++it )
    {
      out << ", ";
      (*it)->print( out );
    }
  }
  out << ")";
}

void VoidType::print( std::ostream &out ) const
{
  out << "void";
}

void StructType::print( std::ostream &out ) const
{
  out << "struct {";

  auto it = elements.begin();
  if ( it != elements.end() )
  {
    it->second->print( out );
    ++it;
    for ( ; it != elements.end(); ++it )
    {
      out << ", ";
      it->second->print( out );
    }
  }

  out << "}";
}

void PtrType::print( std::ostream &out ) const
{
  this->innerType->print( out );
  out << "*";
}

void BasicType::print( std::ostream &out ) const
{
  out << name;
}
