//===--- Token.cc ---------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the tokens.
//
//===----------------------------------------------------------------------===//

#include "Token.h"

#include <iostream>
#include "../Support/Diagnostic.h"

using namespace C4;
using namespace Lex;

Token & Token::clone() const
{
	return *( new Token( *this ) );
}

std::ostream & Lex::operator<<( std::ostream &out, Token const &tok )
{
  auto res = TokenKindNames.find( tok.kind );
  out << res->second << " " << tok.text;
  return out;
}

void Token::dump() const
{
  std::cout << *this;
}
