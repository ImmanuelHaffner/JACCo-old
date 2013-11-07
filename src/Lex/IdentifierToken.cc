//===--- IdentifierToken.cc -----------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the tokens.
//
//===----------------------------------------------------------------------===//

#include "IdentifierToken.h"

#include "../Support/Diagnostic.h"

using namespace C4;
using namespace Lex;

Token & IdentifierToken::clone() const
{
	return *( new IdentifierToken( *this ) );
}

std::ostream & Lex::operator<<( std::ostream &out, IdentifierToken const &tok )
{
  out << tok.pos << " identifier " << tok.text;
  return out;
}

void IdentifierToken::dump() const
{
  std::cout << *this;
}
