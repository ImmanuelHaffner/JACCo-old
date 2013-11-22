//===--- Variable.cc ------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements the Abstract Syntax tree interface.
//
//===----------------------------------------------------------------------===//

#include "Variable.h"


using namespace C4;
using namespace Lex;
using namespace AST;


Variable::Variable( Token tok ) : tok(tok)
{
  assert( tok.kind == TK::IDENTIFIER && "token must be an identifier" );
}

std::ostream & AST::operator<<( std::ostream &out, Variable const &var )
{
  out << "Variable";
  return out;
}
