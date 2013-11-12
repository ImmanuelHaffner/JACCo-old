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

Token & KeywordToken::clone() const
{
	return *( new KeywordToken( *this ) );
}
