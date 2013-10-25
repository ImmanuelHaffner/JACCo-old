//===--- Lexer.cc ---------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements the lexer interface.
//
//===----------------------------------------------------------------------===//

#include "Lexer.h"

#include <iostream>
#include <string>
#include "Token.h"
#include "../Support/CharUtils.h"

using namespace C4;
using namespace Lex;

Lexer::Lexer( SourceBuffer &buf ) : tokenCount(0), buf(buf),
	pos( buf.getSourceFileName(), 1, 1 ), it( buf.getBufStart() )
{}

Lexer::~Lexer() {}

Token * Lexer::getToken()
{
	// if we already reached the end of the line, return NULL
	if ( buf.isBufEnd( it ) )
		return NULL;

	// skip whitespaces
	while ( isWhiteSpace( *it ) )
	{
		// update Pos
		if ( isNewLine( *it ) )
		{
			pos.column = 1;
			++pos.line;
		}
		else
			++pos.column;

		// go to next character
		++it;

		if ( buf.isBufEnd( it ) )
			return NULL;
	}

	Pos start(pos);
	auto index(it);
	std::string TokenText = "";
	TokenText += *it;
	TokenKind kind = TokenKind::IllegalIdentifier;

	if ( isNonDigit( *it ) )
	{	// KEYWORD or IDENTIFIER
		++it;
		++pos.column;

		// Read in the rest of the identifier string
		while ( isNonDigit( *it ) || isDigit( *it ) )
		{
			TokenText += *it;
			++pos.column;
			++it;
		}

		// Compare the identifier string to the keywords
		auto elem = Keywords.find( TokenText );
		if ( elem != Keywords.end() )
			// KEYWORD
			kind = TokenKind::Keyword;
		else
			// IDENTIFIER
			kind = TokenKind::Identifier;

	}
	else if ( isDigit( *it ) )
	{	// CONSTANT or ILLEGAL IDENTIFIER
		++it;
		++pos.column;

		bool illegal = false;

		// Read in the rest of the digit string
		while ( isDigit( *it ) || isNonDigit( *it ) )
		{
			illegal |= isNonDigit( *it );
			TokenText += *it;
			++pos.column;
			++it;
		}

		if ( ! illegal )
			kind = TokenKind::Constant;
	}

	// Create the token with the given type
	return new Token( getTokenID(),
			TokenText.c_str(),
			kind,
			*( new SourceLocation( start, index ) ) );
}
