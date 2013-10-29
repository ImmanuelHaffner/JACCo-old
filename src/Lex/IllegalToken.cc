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

    case IllegalTokenKind::ESCAPE_SEQUENCE:
      str = "illegal escape sequence\n";
  }

  OUT( this->pos, str, this->text );
}
