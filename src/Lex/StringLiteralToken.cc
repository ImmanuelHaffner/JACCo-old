//===--- StringLiteralToken.cc --------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the tokens.
//
//===----------------------------------------------------------------------===//

#include "StringLiteralToken.h"

#include "../Support/Diagnostic.h"

using namespace C4;
using namespace Lex;

Token & StringLiteralToken::clone() const
{
	return *( new StringLiteralToken( *this ) );
}

std::ostream & Lex::operator<<( std::ostream &out, StringLiteralToken const &tok )
{
  out << tok.pos << " string-literal " << tok.text;
  return out;
}

void StringLiteralToken::dump() const
{
  std::cout << *this;
}
