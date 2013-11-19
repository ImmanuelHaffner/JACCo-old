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

std::ostream & Lex::operator<<( std::ostream &out, TokenKind kind )
{
	auto it = TokenKindNames.find( kind );
	if ( it != TokenKindNames.end() )
		out << it->second;
	else
		out << "unresolved token kind";

	return out;
}

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
  out << kind;
  if ( kind != TokenKind::END_OF_FILE )
    out << " " << text;
}
