//===--- Lexer.cc ---------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements the lexer interface.
//
//===----------------------------------------------------------------------===//

#include "Lexer.h"

#include <string>
#include "Token.h"
#include "../Support/CharUtils.h"
#include "../Support/Diagnostic.h"

using namespace C4;
using namespace Lex;

Lexer::Lexer( SourceBuffer &buf ) : tokenCount(0), buf(buf),
	pos( buf.getSourceFileName(), 1, 0 ), it( buf.getBufStart() )
{}

Lexer::~Lexer() {}

Token * Lexer::getToken()
{
	// if we already reached the end of the file, return NULL
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

	TokenKind kind = TokenKind::Illegal;

	if ( isNonDigit( lastChar ) )
	{
		/*
		 * KEYWORD or IDENTIFIER
		 */

		// Read in the rest of the identifier string
		while ( isNonDigit( *it ) || isDigit( *it ) )
		{
			step( lastChar );
			TokenText += lastChar;
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
	{
		/*
		 * DIGITAL CONSTANT
		 */
		
		// Read in the rest of the digit string
		while ( isDigit( *it ) )
		{
			step( lastChar );
			TokenText += lastChar;
		}

    if ( isNonDigit( *it ) )
    {
      // Illegal Identifier

      // Read in the rest of the identifier string
      while ( isNonDigit( *it ) || isDigit( *it ) )
      {
        step( lastChar );
        TokenText += lastChar;
      }

      ERROR( pos, "illegal character sequence: ", TokenText );
    }
    else
      kind = TokenKind::Constant;
	}
	else if ( lastChar == '\'' )
	{
		/*
		 * CHARACTER CONSTANT
		 */

    kind = TokenKind::Constant;
    bool illegalEscapeSequence = false;
    unsigned length = 0;

    while ( *it != '\'' ) // read until the terminating apostrophe
    {
      if ( *it == '\n' ) // look-ahead for newline
        break;

      if ( *it == '\\' )
      { // check for escaped characters
        step( lastChar );
        TokenText += lastChar;
        switch ( *it )
        {
          case '\"':
          case '\'':
          case '?':
          case '\\':
          case 'a':
          case 'b':
          case 'f':
          case 'n':
          case 'r':
          case 't':
          case 'v':
            break;

				default:
            // ILLEGAL CHARACTER
            // illegal escape-sequence
            illegalEscapeSequence = true;
        }
      }
      ++length;
      step( lastChar );
      TokenText += lastChar;
    } // end while

    // read terminating apostrophe
    if ( *it != '\n' )
    {
      assert( *it == '\'' && "wrong character-constant terminator" );

      step( lastChar );
      TokenText += lastChar;

      if ( illegalEscapeSequence )
      {
        kind = TokenKind::Illegal;
        ERROR( pos, "illegal character-constant: ", TokenText, " - ",
            "illegal escape-sequence" );
      }
      else if ( length > 0 )
      {
        kind = TokenKind::Illegal;
        ERROR( pos, "illegal character-constant: ", TokenText, " - ",
            "character-constant with multiple characters" );
      }
    }
    else
    {
      // ILLEGAL CHARACTER
      // missing terminating apostrophe
      ++it;
      kind = TokenKind::Illegal;
      ERROR( pos, "illegal escape sequence: ", TokenText, " - ",
          "missing terminating apostrophe" );
    }
  }
  else if ( lastChar == '\"' )
  {
    /*
     * STRING-LITERAL
     */
    kind = TokenKind::StringLiteral;
    bool illegalEscapeSequence = false;

    while ( *it != '\"' ) // read until the terminating queote
    {
      if ( *it == '\n' ) // look-ahead for newline
        break;

      if ( *it == '\\' )
      { // check for escaped characters
        step( lastChar );
        TokenText += lastChar;
        switch ( *it )
        {
          case '\"':
          case '\'':
          case '?':
          case '\\':
          case 'a':
          case 'b':
          case 'f':
          case 'n':
          case 'r':
          case 't':
          case 'v':
            break;

				default:
            // ILLEGAL CHARACTER
            // illegal escape-sequence
            illegalEscapeSequence = true;
            kind = TokenKind::Illegal;
        }
      }
      step( lastChar );
      TokenText += lastChar;
    } // end while

    // read terminating quote
    if ( *it != '\n' )
    {
      assert( *it == '\"' && "wrong string-literal terminator" );

      step( lastChar );
      TokenText += lastChar;

      if ( illegalEscapeSequence )
      {
        ERROR( pos, "illegal string-literal: ", TokenText, " - ",
            "illegal escape-sequence" );
      }
    }
    else
    {
      // ILLEGAL CHARACTER
      // missing terminating apostrophe
      ++it;
      kind = TokenKind::Illegal;
      ERROR( pos, "illegal string-literal: ", TokenText, " - ",
          "missing terminating quote" );
    }
	}
	else
	{
		/*
		 * PUNCTUATORS
		 */

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

			default:
        // ILLEGAL SEQUENCE OF CHARACTERS
				// if we reach this point, we have found an illegal sequence of
				// characters
        ERROR( pos, "illegal character sequence: ", TokenText );

		} // end switch-case
	} // end PUNCTUATORS


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
