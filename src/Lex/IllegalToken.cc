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
      str = "unknwon token\n";
      break;

    case IllegalTokenKind::IDENTIFIER:
      str = "illegal identifier\n";
      break;

    case IllegalTokenKind::CONSTANT_MULTIPLE_CHARACTERS:
      str = "illegal character-constant\n";

    case IllegalTokenKind::MISSING_TERMINATOR:
      if ( kind == TokenKind::CONSTANT )
        str += "missing terminating apostrophe";
      else if ( kind == TokenKind::STRING_LITERAL )
        str += "missing terminating quote";
      else
        str += "missing unknown terminator";

    case IllegalTokenKind::ESCAPE_SEQUENCE:
      str = "illegal escape sequence\n";
  }

  OUT( this->pos, str, this->text );
}
