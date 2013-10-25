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
	pos( buf.getSourceFileName(), 1, 0 ), it( buf.getBufStart() )
{}

Lexer::~Lexer() {}

Token * Lexer::getToken()
{
	// if we already reached the end of the line, return NULL
	if ( buf.isBufEnd( it ) )
		return NULL;

	char lastChar = ' ';

	// skip whitespaces
	while ( isWhiteSpace( lastChar ) )
	{
		step( lastChar );

		if ( buf.isBufEnd( it ) )
			return NULL;
	}

	Pos start(pos);
	auto index((--it)++); // need to get the position right before it

	std::string TokenText = "";
	TokenText += lastChar;
	assert( *index == lastChar && "wrong index" );

	TokenKind kind = TokenKind::IllegalIdentifier;

	if ( isNonDigit( lastChar ) )
	{	// KEYWORD or IDENTIFIER

		step( lastChar );
		
		// Read in the rest of the identifier string
		while ( isNonDigit( lastChar ) || isDigit( lastChar ) )
		{
			TokenText += lastChar;
			step( lastChar );
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
	else if ( isDigit( lastChar ) )
	{	// CONSTANT or ILLEGAL IDENTIFIER
		
		step( lastChar );

		bool illegal = false;

		// Read in the rest of the digit string
		while ( isDigit( lastChar ) || isNonDigit( lastChar ) )
		{

			illegal |= isNonDigit( lastChar );
			TokenText += lastChar;

			step( lastChar );
		}

		if ( ! illegal )
			kind = TokenKind::Constant;
	}
	else
	{	// PUNTUATORS

		switch ( lastChar )
		{
			case '(':
			case ')':
			case ',':
			case ':':
			case ';':
			case '?':
			case '[':
			case ']':
			case '{':
			case '}':
			case '~':
				kind = TokenKind::Punctuator;
				break;

			case '!':
				if ( *it == '=' )
				{ // !=
					step( lastChar );
					TokenText += lastChar;
				}
				kind = TokenKind::Punctuator;
				break;

			case '#':
				if ( *it == '#' )
				{ // ##
					step( lastChar );
					TokenText += lastChar;
				}
				kind = TokenKind::Punctuator;
				break;

			case '%':
				if ( *it == '=' )
				{
					// %=
					step( lastChar );
					TokenText += lastChar;
				}
				kind = TokenKind::Punctuator;
				break;

			case '&':
				if ( *it == '&' )
				{ // &&
					step( lastChar );
					TokenText += lastChar;
				}
				else if ( *it == '=' )
				{ // &=
					step( lastChar );
					TokenText += lastChar;
				}
				kind = TokenKind::Punctuator;
				break;

			case '*':
				if ( *it == '=' )
				{ // *=
					step( lastChar );
					TokenText += lastChar;
				}
				kind = TokenKind::Punctuator;
				break;

			case '+':
				if ( *it == '+' )
				{ // ++
					step( lastChar );
					TokenText += lastChar;
				}
				else if ( *it == '=' )
				{ // +=
					step( lastChar );
					TokenText += lastChar;
				}
				kind = TokenKind::Punctuator;
				break;

			case '-':
				if ( *it == '-' )
				{ // --
					step( lastChar );
					TokenText += lastChar;
				}
				else if ( *it == '=' )
				{ // -=
					step( lastChar );
					TokenText += lastChar;
				}
				else if ( *it == '>' )
				{ // ->
					step( lastChar );
					TokenText += lastChar;
				}
				kind = TokenKind::Punctuator;
				break;

			case '.':
				/*
				 * Note: for this special case we have to do backtracking
				 */
				if ( *it == '.' )
				{
					if ( *(++it) == '.' )
					{ // ...
						--it;
						step( lastChar );
						TokenText += lastChar;
						step( lastChar );
						TokenText += lastChar;
					}
					else
						--it;
				}
				kind = TokenKind::Punctuator;
				break;

			case '/':
				if ( *it == '=' )
				{ // /=
					step( lastChar );
					TokenText += lastChar;
				}
				kind = TokenKind::Punctuator;
				break;

			case '<':
				if ( *it == '=' )
				{ // <=
					step( lastChar );
					TokenText += lastChar;
				}
				else if ( *it == '<' )
				{ // <<
					step( lastChar );
					TokenText += lastChar;

					if ( *it == '=' )
					{ // <<=
						step( lastChar );
						TokenText += lastChar;
					}
				}
				kind = TokenKind::Punctuator;
				break;

			case '=':
				if ( *it == '=' )
				{ // ==
					step( lastChar );
					TokenText += lastChar;
				}
				kind = TokenKind::Punctuator;
				break;

			case '>':
				if ( *it == '=' )
				{ // >=
					step( lastChar );
					TokenText += lastChar;
				}
				else if ( *it == '>' )
				{ // >>
					step( lastChar );
					TokenText += lastChar;

					if ( *it == '=' )
					{ // >>=
						step( lastChar );
						TokenText += lastChar;
					}
				}
				kind = TokenKind::Punctuator;
				break;

			case '^':
				if ( *it == '=' )
				{ // ^=
					step( lastChar );
					TokenText += lastChar;
				}
				kind = TokenKind::Punctuator;
				break;

			case '|':
				if ( *it == '=' )
				{ // |=
					step( lastChar );
					TokenText += lastChar;
				}
				else if ( *it == '|' )
				{ // ||
					step( lastChar );
					TokenText += lastChar;
				}
				kind = TokenKind::Punctuator;
				break;
		}
	}


	/*
	 * Ok, we have read a token!
	 * Lets just handle the last remaining character
	 */
	if ( isNewLine( lastChar ) )
	{
		// Reset the pos column to 0 (see Lexer constructor)
		// We need to do this, since every time we invoke getToken(), a whitespace
		// is prepended, and the column is increased by one
		pos.column = 0;
		++pos.line;
	}

	// Create the token with the given type
	return new Token( getTokenID(),
			TokenText.c_str(),
			kind,
			*( new SourceLocation( start, index ) ) );
}

void Lexer::step( char &lastChar )
{
	// update Pos
	if ( isNewLine( lastChar ) )
	{
		pos.column = 1;
		++pos.line;
	}
	else
		++pos.column;

	// go to next character
	lastChar = *it;
	++it;

	skipEscapedNewline( lastChar );
}

void Lexer::skipEscapedNewline( char &lastChar )
{
	if ( lastChar == '\\' && isNewLine( *it ) )
	{
		++it;
		lastChar = *it;
		++it;
		skipEscapedNewline( lastChar );

		// skip whitespaces
		while ( isWhiteSpace( lastChar ) )
		{
			if ( buf.isBufEnd( it ) )
				break;

			// update Pos
			if ( isNewLine( lastChar ) )
			{
				pos.column = 1;
				++pos.line;
			}
			else
				++pos.column;

			// go to next character
			lastChar = *it;
			++it;
			skipEscapedNewline( lastChar );
		}
	}
}

