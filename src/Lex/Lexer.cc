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
	pos( buf.getFileName().c_str(), 1, 0 ), it( buf.begin() )
{
	if ( ! buf.isInitialized() )
		buf.init();
}

Lexer::~Lexer() {}

Token * Lexer::getToken()
{
	char lastChar = ' ';

	// skip whitespaces and comments
  if ( ! skip( lastChar ) )
    return NULL;

	Pos const start( pos );
	auto index( (--it)++ ); // need to get the position right before it
	assert( *index == lastChar && "wrong index" );

	std::string TokenText = "";
	TokenText += lastChar;
	TokenKind kind = TokenKind::Illegal;

  if ( isNonDigit( lastChar ) )
	{
		/*
		 * KEYWORD or IDENTIFIER
		 */

		// Read in the rest of the identifier string
		while ( isNonDigit( *it ) || isDigit( *it ) )
		{
			if ( ! step( lastChar ) )
        break;

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
			if ( ! step( lastChar ) )
        break;

			TokenText += lastChar;
		}

    if ( isNonDigit( *it ) )
    {
      // Illegal Identifier

      // Read in the rest of the identifier string
      while ( isNonDigit( *it ) || isDigit( *it ) )
      {
        if ( ! step( lastChar ) )
          break;

        TokenText += lastChar;
      }

      ERROR( start, "illegal character sequence\n", TokenText, "    - ",
          "identifiers must start with an alphabetical char or an underscore" );
    }
    else
      kind = TokenKind::Constant;
	}
	else if ( lastChar == '\'' )
	{
		/*
		 * CHARACTER CONSTANT
		 */
    step ( lastChar );

    kind = TokenKind::Constant;
    bool illegalEscapeSequence = false;
    unsigned length = 0;

    while ( lastChar != '\'' ) // read until the terminating apostrophe
    {
      if ( isNewLine( lastChar ) )
      {
        break;
      }

      if ( lastChar == '\\' )
      { // check for escaped characters
        TokenText += lastChar;
        step( lastChar );
        switch ( lastChar )
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
      TokenText += lastChar;
      step( lastChar );
      ++length;
    } // end while

    // read terminating apostrophe
    if ( isNewLine( lastChar ) )
    {
      // ILLEGAL CHARACTER
      // missing terminating apostrophe
      kind = TokenKind::Illegal;
      if ( length <= 1 )
      {
        ERROR( pos,
            "illegal character-constant\n", TokenText, "    - ",
            "missing terminating apostrophe" );
      }
      else
      {
        ERROR( Pos( start.name, start.line, start.column + 2 ),
            "illegal character-constant\n", TokenText, "    - ",
            "missing terminating apostrophe" );
      }
    }
    else  //( lastChar == '\'' )
    {
      assert( lastChar == '\'' && "missing terminating apostrophe" );
      TokenText += lastChar;

      if ( length > 1 )
      {
        kind = TokenKind::Illegal;
        ERROR( start, "illegal character-constant\n", TokenText, "    - ",
            "character-constant with multiple characters" );
      }
      else if ( illegalEscapeSequence )
      {
        kind = TokenKind::Illegal;
        ERROR( start, "illegal character-constant\n", TokenText, "    - ",
            "illegal escape-sequence" );
      }
    }
  } // end CHARACTER-CONSTANT
  else if ( lastChar == '\"' )
  {
    /*
     * STRING-LITERAL
     */
    step( lastChar );

    kind = TokenKind::StringLiteral;
    Pos * illegalEscapePos = NULL;

    while ( lastChar != '\"' ) // read until the terminating quote
    {
      if ( isNewLine( lastChar ) )
      {
        break;
      }

      if ( lastChar == '\\' )
      { // check for escaped characters
        TokenText += lastChar;
        step( lastChar );
        switch ( lastChar )
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
						if ( ! illegalEscapePos )
							illegalEscapePos = new Pos(pos);
        }
      }
      TokenText += lastChar;
      step( lastChar );
    } // end while

    // read terminating quote
    if ( isNewLine( lastChar ) )
    {
      // ILLEGAL CHARACTER
      // missing terminating quote
      kind = TokenKind::Illegal;
      ERROR( pos,
          "illegal string-literal\n", TokenText, "    - ",
          "missing terminating quote" );
    }
    else
    {
      assert( lastChar == '\"' && "missing terminating quote" );

      TokenText += lastChar;
      step( lastChar );

      if ( illegalEscapePos )
      {
				assert( illegalEscapePos && "no position set" );

        kind = TokenKind::Illegal;
        ERROR( *illegalEscapePos, "illegal string-literal\n", TokenText,
						"    - ", "illegal escape-sequence" );

				delete illegalEscapePos;
      }
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
        ERROR( start, "illegal character sequence\n", TokenText );

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

bool Lexer::step( char &lastChar )
{
  if ( it == buf.end() )
    return false;

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

	return skipEscapedNewline( lastChar );
}

bool Lexer::skip( char &lastChar )
{
  while ( true )
  {
    if ( it == buf.end() )
      return false;

    if ( isWhiteSpace( lastChar ) )
    {
      if ( ! step( lastChar ) )
        return false;
    }
    else if ( lastChar == '/' )
    {
      if ( *it == '/' )
      {
        // single-line comment
        // read until the end of the line
        if ( ! step( lastChar ) )
          return false;
        if ( ! step( lastChar ) )
          return false;

        while ( ! isNewLine( lastChar ) )
        {
          if ( ! step( lastChar ) )
            return false;
        }
      }
      else if ( *it == '*' )
      {
        // comment-block
        // read until first */
        //
        // CARE for /*/
        if ( ! step( lastChar ) )
          return false;
        if ( ! step( lastChar ) )
          return false;

        while ( lastChar != '*' || *it != '/' )
        {
          if ( ! step( lastChar ) )
            return false;
        }
      }
      else
        return true;
    } // end if lastChar == '/'
    else
      return true;
  } // end while
  return true;
}

bool Lexer::skipEscapedNewline( char &lastChar )
{
  if ( it == buf.end() )
    return false;

	if ( lastChar == '\\' && isNewLine( *it ) )
	{
    ++pos.line;
    pos.column = 1;

    // set lastChar to the next char behind \ + Newline
		++it;
    if ( it == buf.end() )
      return false;

		lastChar = *it;
		++it;
    if ( it == buf.end() )
      return false;

    // skip following whitespaces and comments
    return skip( lastChar );
	}

  return true;
}
