//===--- PunctuatorToken.cc -----------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the tokens.
//
//===----------------------------------------------------------------------===//

#include "PunctuatorToken.h"

#include "../Support/Diagnostic.h"

using namespace C4;
using namespace Lex;

void PunctuatorToken::dump() const
{
  OUT( this->pos, "punctuator: ", this->text );
}
