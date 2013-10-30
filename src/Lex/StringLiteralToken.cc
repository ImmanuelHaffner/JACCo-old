//===--- StringLiteralToken.cc --------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the tokens.
//
//===----------------------------------------------------------------------===//

#include "StringLiteralToken.h"

#include "../Support/Diagnostic.h"

using namespace C4;
using namespace Lex;

void StringLiteralToken::dump() const
{
  OUT( this->pos, "string-literal: ", this->text );
}
