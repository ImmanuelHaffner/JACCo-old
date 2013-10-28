//===--- IdentifierToken.cc -----------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the tokens.
//
//===----------------------------------------------------------------------===//

#include "IdentifierToken.h"

#include "../Support/Diagnostic.h"

using namespace C4;
using namespace Lex;

void IdentifierToken::dump() const
{
  OUT( this->pos, " identifier: ", this->text );
}
