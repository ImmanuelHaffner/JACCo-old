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

std::ostream & Lex::operator<<( std::ostream &out, IllegalToken const &tok )
{
  out << tok.pos;
  out << " illegal token: " << tok.text << " - ";
  switch ( tok.iKind )
  {
    case IllegalTokenKind::UNKNOWN:
      out << "unknown token";
      break;

    case IllegalTokenKind::IDENTIFIER:
      out << "illegal identifier";
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

  return out;
}

void IllegalToken::dump() const
{
  std::cout << *this;
}
