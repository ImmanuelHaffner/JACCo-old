//===--- StringLiteral.cc -------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements the Abstract Syntax tree interface.
//
//===----------------------------------------------------------------------===//

#include "StringLiteral.h"


using namespace C4;
using namespace Lex;
using namespace AST;


StringLiteral::StringLiteral( Token tok ) : tok(tok)
{
  assert( tok.kind == TK::STRING_LITERAL && "token must be a string-literal" );
}

std::ostream & AST::operator<<( std::ostream &out, StringLiteral const &lit )
{
  out << "StringLiteral";
  return out;
}
