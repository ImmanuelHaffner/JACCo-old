//===--- Token.cc ---------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the tokens.
//
//===----------------------------------------------------------------------===//

#include "Token.h"

#include <iostream>

using namespace C4;
using namespace Lex;

Token & Token::clone() const
{
  return *( new Token( *this ) );
}

std::ostream & Lex::operator<<( std::ostream &out, Token const &tok )
{
  tok.dump( out );
  return out;
}

void Token::dump( std::ostream &out /*= std::cout*/ ) const
{
  auto res = TokenKindNames.find( kind );
  out << res->second << " " << text;
}
