//===--- ConstantToken.cc -------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the tokens.
//
//===----------------------------------------------------------------------===//

#include "ConstantToken.h"

#include "../Support/Diagnostic.h"

using namespace C4;
using namespace Lex;

void ConstantToken::dump() const
{
  OUT( this->pos, "constant: ", this->text );
}
