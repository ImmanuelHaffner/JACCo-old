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

Lexer::Lexer( char const * const fileName, FILE * file ) : file(file),
  fileName(fileName), pos(fileName, 1, 0)
{}

Lexer::Lexer( std::string const &fileName, FILE * file ) : file(file),
  fileName(fileName), pos(fileName.c_str(), 1, 0)
{}

Lexer::~Lexer() {}

Token * Lexer::getToken()
{
  //int current = ' ';
  //
  //// skip whitespaces and comments
  //if ( ! skip( current ) )
  //return NULL;
  //
  //Pos const start( pos );
  //auto index( (--it)++ ); // need to get the position right before it
  //
  //std::string TokenText = "";
  //TokenText += current;
  //TokenKind kind = TokenKind::Illegal;
  //
  //if ( isNonDigit( current ) )
  //{
  ///*
  //* KEYWORD or IDENTIFIER
  //*/
  //return readKeywordOrIdentifier( current );
  //}
  //else if ( isDigit( current ) )
  //{
  ///*
  //* DIGITAL CONSTANT
  //*/
  //
  //// Read in the rest of the digit string
  //while ( isDigit( *it ) )
  //{
  //if ( ! step( current ) )
  //break;
  //
  //TokenText += current;
  //}
  //
  //if ( isNonDigit( *it ) )
  //{
  //// Illegal Identifier
  //
  //// Read in the rest of the identifier string
  //while ( isNonDigit( *it ) || isDigit( *it ) )
  //{
  //if ( ! step( current ) )
  //break;
  //
  //TokenText += current;
  //}
  //
  //ERROR( start, "illegal character sequence\n", TokenText, "    - ",
  //"identifiers must start with an alphabetical char or an underscore" );
  //}
  //else
  //kind = TokenKind::Constant;
  //}
  //else if ( current == '\'' )
  //{
  ///*
  //* CHARACTER CONSTANT
  //*/
  //step ( current );
  //
  //kind = TokenKind::Constant;
  //bool illegalEscapeSequence = false;
  //unsigned length = 0;
  //
  //while ( current != '\'' ) // read until the terminating apostrophe
  //{
  //if ( isNewLine( current ) )
  //{
  //break;
  //}
  //
  //if ( current == '\\' )
  //{ // check for escaped characters
  //TokenText += current;
  //step( current );
  //switch ( current )
  //{
  //case '\"':
  //case '\'':
  //case '?':
  //case '\\':
  //case 'a':
  //case 'b':
  //case 'f':
  //case 'n':
  //case 'r':
  //case 't':
  //case 'v':
  //break;
  //
  //default:
  //// ILLEGAL CHARACTER
  //// illegal escape-sequence
  //illegalEscapeSequence = true;
  //}
  //}
  //TokenText += current;
  //step( current );
  //++length;
  //} // end while
  //
  //// read terminating apostrophe
  //if ( isNewLine( current ) )
  //{
  //// ILLEGAL CHARACTER
  //// missing terminating apostrophe
  //kind = TokenKind::Illegal;
  //if ( length <= 1 )
  //{
  //ERROR( pos,
  //"illegal character-constant\n", TokenText, "    - ",
  //"missing terminating apostrophe" );
  //}
  //else
  //{
  //ERROR( Pos( start.name, start.line, start.column + 2 ),
  //"illegal character-constant\n", TokenText, "    - ",
  //"missing terminating apostrophe" );
  //}
  //}
  //else  //( current == '\'' )
  //{
  //assert( current == '\'' && "missing terminating apostrophe" );
  //TokenText += current;
  //
  //if ( length > 1 )
  //{
  //kind = TokenKind::Illegal;
  //ERROR( start, "illegal character-constant\n", TokenText, "    - ",
  //"character-constant with multiple characters" );
  //}
  //else if ( illegalEscapeSequence )
  //{
  //kind = TokenKind::Illegal;
  //ERROR( start, "illegal character-constant\n", TokenText, "    - ",
  //"illegal escape-sequence" );
  //}
  //}
  //} // end CHARACTER-CONSTANT
  //else if ( current == '\"' )
  //{
  ///*
  //* STRING-LITERAL
  //*/
  //step( current );
  //
  //kind = TokenKind::StringLiteral;
  //Pos * illegalEscapePos = NULL;
  //
  //while ( current != '\"' ) // read until the terminating quote
  //{
  //if ( isNewLine( current ) )
  //{
  //break;
  //}
  //
  //if ( current == '\\' )
  //{ // check for escaped characters
  //TokenText += current;
  //step( current );
  //switch ( current )
  //{
  //case '\"':
  //case '\'':
  //case '?':
  //case '\\':
  //case 'a':
  //case 'b':
  //case 'f':
  //case 'n':
  //case 'r':
  //case 't':
  //case 'v':
  //break;
  //
  //default:
  //// ILLEGAL CHARACTER
  //// illegal escape-sequence
  //if ( ! illegalEscapePos )
  //illegalEscapePos = new Pos(pos);
  //}
  //}
  //TokenText += current;
  //step( current );
  //} // end while
  //
  //// read terminating quote
  //if ( isNewLine( current ) )
  //{
  //// ILLEGAL CHARACTER
  //// missing terminating quote
  //kind = TokenKind::Illegal;
  //ERROR( pos,
  //"illegal string-literal\n", TokenText, "    - ",
  //"missing terminating quote" );
  //}
  //else
  //{
  //assert( current == '\"' && "missing terminating quote" );
  //
  //TokenText += current;
  //step( current );
  //
  //if ( illegalEscapePos )
  //{
  //assert( illegalEscapePos && "no position set" );
  //
  //kind = TokenKind::Illegal;
  //ERROR( *illegalEscapePos, "illegal string-literal\n", TokenText,
  //"    - ", "illegal escape-sequence" );
  //
  //delete illegalEscapePos;
  //}
  //}
  //}
  //else
  //{
  ///*
  //* PUNCTUATORS
  //*/
  //
  //switch ( current )
  //{
  //case '(':
  //case ')':
  //case ',':
  //case ':':
  //case ';':
  //case '?':
  //case '[':
  //case ']':
  //case '{':
  //case '}':
  //case '~':
  //kind = TokenKind::Punctuator;
  //break;
  //
  //case '!':
  //if ( *it == '=' )
  //{ // !=
  //step( current );
  //TokenText += current;
  //}
  //kind = TokenKind::Punctuator;
  //break;
  //
  //case '#':
  //if ( *it == '#' )
  //{ // ##
  //step( current );
  //TokenText += current;
  //}
  //kind = TokenKind::Punctuator;
  //break;
  //
  //case '%':
  //if ( *it == '=' )
  //{
  //// %=
  //step( current );
  //TokenText += current;
  //}
  //kind = TokenKind::Punctuator;
  //break;
  //
  //case '&':
  //if ( *it == '&' )
  //{ // &&
  //step( current );
  //TokenText += current;
  //}
  //else if ( *it == '=' )
  //{ // &=
  //step( current );
  //TokenText += current;
  //}
  //kind = TokenKind::Punctuator;
  //break;
  //
  //case '*':
  //if ( *it == '=' )
  //{ // *=
  //step( current );
  //TokenText += current;
  //}
  //kind = TokenKind::Punctuator;
  //break;
  //
  //case '+':
  //if ( *it == '+' )
  //{ // ++
  //step( current );
  //TokenText += current;
  //}
  //else if ( *it == '=' )
  //{ // +=
  //step( current );
  //TokenText += current;
  //}
  //kind = TokenKind::Punctuator;
  //break;
  //
  //case '-':
  //if ( *it == '-' )
  //{ // --
  //step( current );
  //TokenText += current;
  //}
  //else if ( *it == '=' )
  //{ // -=
  //step( current );
  //TokenText += current;
  //}
  //else if ( *it == '>' )
  //{ // ->
  //step( current );
  //TokenText += current;
  //}
  //kind = TokenKind::Punctuator;
  //break;
  //
  //case '.':
  ///*
  //* Note: for this special case we have to do backtracking
  //*/
  //if ( *it == '.' )
  //{
  //if ( *(++it) == '.' )
  //{ // ...
  //--it;
  //step( current );
  //TokenText += current;
  //step( current );
  //TokenText += current;
  //}
  //else
  //--it;
  //}
  //kind = TokenKind::Punctuator;
  //break;
  //
  //case '/':
  //if ( *it == '=' )
  //{ // /=
  //step( current );
  //TokenText += current;
  //}
  //kind = TokenKind::Punctuator;
  //break;
  //
  //case '<':
  //if ( *it == '=' )
  //{ // <=
  //step( current );
  //TokenText += current;
  //}
  //else if ( *it == '<' )
  //{ // <<
  //step( current );
  //TokenText += current;
  //
  //if ( *it == '=' )
  //{ // <<=
  //step( current );
  //TokenText += current;
  //}
  //}
  //kind = TokenKind::Punctuator;
  //break;
  //
  //case '=':
  //if ( *it == '=' )
  //{ // ==
  //step( current );
  //TokenText += current;
  //}
  //kind = TokenKind::Punctuator;
  //break;
  //
  //case '>':
  //if ( *it == '=' )
  //{ // >=
  //step( current );
  //TokenText += current;
  //}
  //else if ( *it == '>' )
  //{ // >>
  //step( current );
  //TokenText += current;
  //
  //if ( *it == '=' )
  //{ // >>=
  //step( current );
  //TokenText += current;
  //}
  //}
  //kind = TokenKind::Punctuator;
  //break;
  //
  //case '^':
  //if ( *it == '=' )
  //{ // ^=
  //step( current );
  //TokenText += current;
  //}
  //kind = TokenKind::Punctuator;
  //break;
  //
  //case '|':
  //if ( *it == '=' )
  //{ // |=
  //step( current );
  //TokenText += current;
  //}
  //else if ( *it == '|' )
  //{ // ||
  //step( current );
  //TokenText += current;
  //}
  //kind = TokenKind::Punctuator;
  //break;
  //
  //default:
  //// ILLEGAL SEQUENCE OF CHARACTERS
  //// if we reach this point, we have found an illegal sequence of
  //// characters
  //ERROR( start, "illegal character sequence\n", TokenText );
  //
  //} // end switch-case
  //} // end PUNCTUATORS
  //
  //
  ///*
  //* Ok, we have read a token!
  //* Lets just handle the last remaining character
  //*/
  //if ( isNewLine( current ) )
  //{
  //// Reset the pos column to 0 (see Lexer constructor)
  //// We need to do this, since every time we invoke getToken(), a whitespace
  //// is prepended, and the column is increased by one
  //pos.column = 0;
  //++pos.line;
  //}
  //
  //// Create the token with the given type
  //return new Token( getTokenID(),
  //TokenText.c_str(),
  //kind,
  //*( new SourceLocation( start, index ) ) );
  return NULL;
}

/// Steps one character forward in the buffer and updates 'it' and
/// 'pos'.
/// Immediately skips escaped newlines
///
/// \return false, iff the end of the buffer is reached, true otherwise
bool Lexer::step( int &current )
{
  // update Pos
  if ( current == '\n' )
  {
    // UNIX Newline
    pos.column = 1;
    ++pos.line;

  } // end UNIX Newline
  else if ( current == '\r' )
  {
    if ( ! feof( file ) )
    {
      if ( ( current = fgetc( file ) ) == '\n' )
      {
        // Windows Newline
        // nothing to do here
        // overread the \r, such that the \n will be handled by the next
        // invokation of step(..)
      }
      else
      {
        // single '\r'
        WARNING( pos, "a wild \\r appeared!" );

        ungetc( current, file );
        current = '\r';
      }
    }
    else
    {
      // single '\r'
      WARNING( pos, "a wild \\r appeared!" );
    }
  } // end '\r'
  else if ( current == '\\' )
  {
    // Check for escaped Newline

    if ( ! feof( file ) )
    {
      if ( ( current = fgetc( file ) ) == '\r' )
      {
        if ( ! feof( file ) )
        {
          if ( ( current = fgetc( file ) ) == '\n' )
          {
            // Windows Newline
          }
          else{
            // single '\r'
            WARNING( pos, "a wild \\r appeared!" );

            ungetc( current, file );
            current = '\r';
          }
        }
        else
        {
          // single '\r'
          WARNING( pos, "a wild \\r appeared!" );
        }
      } // end '\r'

      if ( current == '\n' )
      {
        // Escaped Newline
        if ( ! feof( file ) )
        {
          // Skip until first non-whitespace character, that is not part of a
          // comment
          current = fgetc( file );
          skip( current );

          // push back the last character
          ungetc( current, file );
        }
      } // end '\n'
      else
      {
        ungetc( current, file );
        current = '\\';
      }
    }
  } // end '/'
  else
    // Other character
    ++pos.column;

  current = fgetc( file );
  
  return ! feof( file );
}

/// This method skips until the first non-whitespace character, that
/// is not part of a comment
///
/// \return false, iff the end of the buffer is reached, true otherwise
bool Lexer::skip( int &current )
{
  while ( true )
  {
    if ( isWhiteSpace( current ) )
    {
      if ( ! step( current ) )
        return false;
    }
    else if ( current == '/' )
    {
      if ( ! feof( file ) )
      {
        if ( ( current = fgetc( file ) ) == '/' )
        {
          // line-comment
          while ( step( current ) && current != '\n' );
        }
        else if ( current == '*' )
        {
          // block-comment
        }
        else
        {
          ungetc( current, file );
          current = '/';
        }
      } // end !feof( file )
    } // end if current == '/'
    else
      // non-whitespace character
      break;

    if ( feof( file ) )
      return false;

  } // end while
  return true;
}

Token * Lexer::readKeywordOrIdentifier( int &current )
{
  ///*
  //* KEYWORD or IDENTIFIER
  //*/
  //Pos const start( pos );
  //auto index( (--it)++ ); // need to get the position right before it
  //std::string TokenText = "";
  //TokenText += current;
  //TokenKind kind = TokenKind::Illegal;
  //
  //// Read in the rest of the identifier string
  //while ( isNonDigit( *it ) || isDigit( *it ) )
  //{
  //if ( ! step( current ) )
  //break;
  //
  //TokenText += current;
  //}
  //
  //// Compare the identifier string to the keywords
  //auto elem = Keywords.find( TokenText );
  //if ( elem != Keywords.end() )
  //// KEYWORD
  //kind = TokenKind::Keyword;
  //else
  //// IDENTIFIER
  //kind = TokenKind::Identifier;
  //
  //// Create the token with the given type
  //return new Token( getTokenID(),
  //TokenText.c_str(),
  //kind,
  //*( new SourceLocation( start, index ) ) );
  return NULL;
}
