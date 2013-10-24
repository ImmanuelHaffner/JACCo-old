//===--- Lexer.cc ---------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements the token class.
//
//===----------------------------------------------------------------------===//

#include "Lexer.h"

using namespace C4;
using namespace C4::Lex;

struct Token
{
	Token( unsigned id, char const * const text, TokenKind kind,
			SourceLocation const &loc ) :
		id(id), text(nonNull(text)), kind(kind), loc(loc)
	{}

	unsigned const id;
	char const * const text;
	TokenKind const kind;
	SourceLocation const &loc;
};
