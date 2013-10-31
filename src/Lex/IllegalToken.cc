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

void IllegalToken::dump() const
{
  std::string str;

  switch ( this->iKind )
  {
    case IllegalTokenKind::UNKNOWN:
      str = "unknwon token";
      break;

    case IllegalTokenKind::IDENTIFIER:
      str = "illegal identifier";
      break;

    case IllegalTokenKind::CONSTANT_MULTIPLE_CHARACTERS:
      str = "illegal character-constant";
      break;

    case IllegalTokenKind::MISSING_APOSTROPHE:
      str = "missing terminating apostrophe";
      break;

    case IllegalTokenKind::MISSING_QUOTE:
      str = "missing terminating quote";
      break;

    case IllegalTokenKind::MISSING_COMMENT_TERMINATOR:
      str = "missing terminator of comment block";
      break;

    case IllegalTokenKind::ESCAPE_SEQUENCE:
      str = "illegal escape sequence";
      break;
  }

  if ( this->text.empty() )
    OUT( this->pos, str );
  else
    OUT( this->pos, str, "\n", this->text );
}
