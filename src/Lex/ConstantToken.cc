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

Token & ConstantToken::clone() const
{
	return *( new ConstantToken( *this ) );
}
