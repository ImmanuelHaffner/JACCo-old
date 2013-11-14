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
  out << "illegal token: " << text << " - ";
  switch ( iKind )
  {
    case IllegalTokenKind::UNKNOWN:
      out << "unknown token";
      break;

    case IllegalTokenKind::IDENTIFIER:
      out << "illegal identifier";
      break;

    case IllegalTokenKind::EMPTY_CHARACTER_CONSTANT:
      out << "empty character constant";
      break;

    case IllegalTokenKind::CONSTANT_MULTIPLE_CHARACTERS:
      out << "character constant with multiple characters";
      break;

    case IllegalTokenKind::MISSING_APOSTROPHE:
      out << "missing terminating apostrophe";
      break;

    case IllegalTokenKind::MISSING_QUOTE:
      out << "missing terminating quote";
      break;

    case IllegalTokenKind::MISSING_COMMENT_TERMINATOR:
      out << "unterminated comment block";
      break;

    case IllegalTokenKind::ESCAPE_SEQUENCE:
      out << "illegal escape sequence";
      break;
  }
}
