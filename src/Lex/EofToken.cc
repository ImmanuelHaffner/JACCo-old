//===--- EofToken.cc ------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the tokens.
//
//===----------------------------------------------------------------------===//

#include "EofToken.h"

#include "../Support/Diagnostic.h"

using namespace C4;
using namespace Lex;

Token & EofToken::clone() const
{
	return *( new EofToken( *this ) );
}

std::ostream & Lex::operator<<( std::ostream &out, EofToken const &tok )
{
  out << tok.pos << " end of file";
  return out;
}

void EofToken::dump() const
{
  OUT( this->pos, "end-of-file" );
}
