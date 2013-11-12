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

Token & StringLiteralToken::clone() const
{
	return *( new StringLiteralToken( *this ) );
}
