//===--- Token.cc ---------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements the token.
//
//===----------------------------------------------------------------------===//

#include "Token.h"

#include <iostream>
#include "../Support/CharUtils.h"

using namespace C4::Lex;

void Token::dump() const
{
	std::cout
		<< loc.pos.name << ":"
		<< loc.pos.line << ":"
		<< loc.pos.column << " ";

	switch ( kind )
	{
		case TokenKind::Keyword:
			std::cout << "keyword";
			break;
		case TokenKind::Identifier:
			std::cout << "identifier";
			break;
		case TokenKind::Constant:
			std::cout << "constant";
			break;
		case TokenKind::StringLiteral:
			std::cout << "string-literal";
			break;
		case TokenKind::Punctuator:
			std::cout << "punctuator";
			break;
		case TokenKind::Illegal:
			std::cout << "illegal";
			break;
	}

	std::cout << " " << text << std::endl;
}
