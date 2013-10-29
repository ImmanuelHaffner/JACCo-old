//===--- KeywordToken.cc --------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the tokens.
//
//===----------------------------------------------------------------------===//

#include "KeywordToken.h"

#include "../Support/Diagnostic.h"

using namespace C4;
using namespace Lex;

void KeywordToken::dump() const
{
  OUT( this->pos, "keyword: ", this->text );
}
