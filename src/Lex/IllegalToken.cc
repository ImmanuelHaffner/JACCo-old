//===--- IllegalToken.cc --------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the tokens.
//
//===----------------------------------------------------------------------===//

#include "IllegalToken.h"

#include "../Support/Diagnostic.h"

using namespace C4;
using namespace Lex;


std::ostream & Lex::operator<<( std::ostream &out, IllegalTokenKind iKind )
{
  auto it = IllegalTokenKindNames.find( iKind );
  if ( it != IllegalTokenKindNames.end() )
    out << it->second;
  else
    out << "unresolved illegal token kind";

  return out;
}

Token & IllegalToken::clone() const
{
	return *( new IllegalToken( *this ) );
}

std::ostream & Lex::operator<<( std::ostream &out, IllegalToken const &tok )
{
  tok.dump( out );
  return out;
}

void IllegalToken::dump( std::ostream &out /*= std::cout*/ ) const
{
  out << "illegal token: " << text << " - " << iKind;
}
