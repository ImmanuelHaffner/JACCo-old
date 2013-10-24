//===--- Lexer.cc ---------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements the lexer interface.
//
//===----------------------------------------------------------------------===//

#include "Lexer.h"

using namespace C4;
using namespace Lex;

Lexer::Lexer( SourceBuffer &buf ) : buf(buf)
{
	it = buf.getBufStart();
}

Lexer::~Lexer()
{
}

Token Lexer::getToken()
{
	
}
