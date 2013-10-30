//===--- Token.cc ---------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the tokens.
//
//===----------------------------------------------------------------------===//

#include "Token.h"

#include "../Support/Diagnostic.h"

using namespace C4;
using namespace Lex;

void Token::dump() const
{
	std::string type;

	switch ( kind )
	{
		case TokenKind::KEYWORD:
			type = "keyword";
			break;

		case TokenKind::IDENTIFIER:
			type = "identifier";
			break;

		case TokenKind::CONSTANT:
			type = "constant";
			break;

		case TokenKind::STRING_LITERAL:
			type = "string-literal";
			break;

		case TokenKind::PUNCTUATOR:
			type = "punctuator";
			break;

		default:
			type = "illegal";
	}

  OUT( this->pos, " ", type, ": ", this->text );
}
