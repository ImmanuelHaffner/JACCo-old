//===--- Lexer.cc ---------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements the lexer interface.
//
//===----------------------------------------------------------------------===//

#include "Lexer.h"

#include <iostream>
#include "../Support/CharUtils.h"

using namespace C4;
using namespace Lex;

Lexer::Lexer( SourceBuffer &buf ) :
	buf(buf), pos( buf.getSourceFileName(), 1, 0 ), it( buf.getBufStart() )
{}

Lexer::~Lexer() {}

Token * Lexer::getToken()
{
	char lastChar = ' '; // look-ahead of 1

	// Skip whitespaces
	while ( isWhiteSpace( lastChar ) )
	{
		if ( buf.isBufEnd( it ) )
			return NULL;

		// read next character
		char nextChar = *(it++);

		// update Pos
		if ( isNewLine( nextChar ) )
		{
			pos.column = 1;
			++pos.line;
		}
		else
			++pos.column;

		lastChar = nextChar;
	}

	std::cout << "Pos( \"" << pos.name << "\", " << pos.line << ", "
		<< pos.column << " ) - " << visualizeChar( lastChar ) << std::endl;

	return new Token( 0, "token", TokenKind::Keyword, *( new SourceLocation(
						pos, it ) ) );
}
