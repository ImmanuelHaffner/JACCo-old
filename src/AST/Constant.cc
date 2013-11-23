//===--- Constant.cc ------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements the Abstract Syntax tree interface.
//
//===----------------------------------------------------------------------===//

#include "Constant.h"


using namespace C4;
using namespace Lex;
using namespace AST;


Constant::Constant( Token const tok ) : tok(tok)
{
  assert( tok.kind == TK::CONSTANT && "token must be a constant" );
}

std::ostream & AST::operator<<( std::ostream &out, Constant const &con )
{
  out << "Constant";
  return out;
}
