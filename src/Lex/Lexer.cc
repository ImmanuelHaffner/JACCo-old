//===--- Lexer.cc ---------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements the lexer interface.
//
//===----------------------------------------------------------------------===//

#include "Lexer.h"

#include <string>
#include <cctype>
#include "Token.h"
#include "EofToken.h"
#include "IllegalToken.h"
#include "KeywordToken.h"
#include "IdentifierToken.h"
#include "ConstantToken.h"
#include "StringLiteralToken.h"
#include "PunctuatorToken.h"
#include "../Support/CharUtils.h"
#include "../Support/Diagnostic.h"

using namespace C4;
using namespace Lex;

Lexer::Lexer() : fileName("<stdin>"), file( std::cin ), pos("<stdin>", 1, 1)
{}

Lexer::Lexer( char const * const fileName ) : fileName(fileName),
  file( * new std::ifstream( fileName ) ), pos(fileName, 1, 1)
{}

Lexer::Lexer( std::string const &fileName ) : fileName(fileName),
  file( * new std::ifstream( fileName ) ),
  pos(fileName.c_str(), 1, 1)
{}

Lexer::~Lexer() {}

Token & Lexer::getToken()
{
  if ( ! file.good() )
    return *( new EofToken( pos ) );

  skip();

  if ( ! file.good() )
    return *( new EofToken( pos ) );

  if ( isalpha( file.peek() ) || file.peek() == '_' )
  {
    // Keyword or Identifier
    return readKeywordOrIdentifier();
  }
  else if ( isdigit( file.peek() ) )
  {
    // Numerical Constant
    return readNumericalConstant();
  }
  else if ( file.peek() == '\'' )
  {
    // Character Constant
    return readCharacterConstant();
  }
  else if ( file.peek() == '\"' )
  {
    // String Literal
  }
  //ERROR( pos,
  //"illegal character-constant\n", TokenText, "    - ",
  //"missing terminating apostrophe" );
  //
  //ERROR( Pos( start.name, start.line, start.column + 2 ),
  //"illegal character-constant\n", TokenText, "    - ",
  //"missing terminating apostrophe" );
  //
  //ERROR( start, "illegal character-constant\n", TokenText, "    - ",
  //"character-constant with multiple characters" );
  //
  //ERROR( start, "illegal character-constant\n", TokenText, "    - ",
  //"illegal escape-sequence" );
  ///*
  //* STRING-LITERAL
  //*/
  //
  //ERROR( pos,
  //"illegal string-literal\n", TokenText, "    - ",
  //"missing terminating quote" );
  //
  //ERROR( *illegalEscapePos, "illegal string-literal\n", TokenText,
  //"    - ", "illegal escape-sequence" );
  //
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
  return *( new IllegalToken( pos, IllegalTokenKind::UNKNOWN, "" ) );
}

Pos Lexer::getPos() const
{
  return Pos( this->pos );
}

char Lexer::current() const
{
  return file.peek();
}

Token & Lexer::readKeywordOrIdentifier()
{
  /*
   * KEYWORD or IDENTIFIER
   */
  Pos start( pos );
  std::string text = "";
  updatePos( file.peek() );
  text += file.get();

  while ( file.good() && ( isalnum( file.peek() ) || file.peek() == '_' ) )
  {
    updatePos( file.peek() );
    text += file.get();
  }

  auto it = Keywords.find( text );

  if ( it != Keywords.end() )
  {
    return *( new KeywordToken( start, it->second, text ) );
  }

  return *( new IdentifierToken( start, text ) );
}

Token & Lexer::readNumericalConstant()
{
  /*
   * Numerical CONSTANT
   */
  Pos start( pos );
  std::string text = "";
  updatePos( file.peek() );
  text += file.get();

  bool illegalIdentifier = false;

  while ( file.good() && ( isalnum( file.peek() ) || file.peek() == '_' ) )
  {
    illegalIdentifier = isalpha( file.peek() ) || file.peek() == '_';

    updatePos( file.peek() );
    text += file.get();
  }

  if ( illegalIdentifier )
  {
    // ILLEGAL Identifier
    return *( new IllegalToken( start, IllegalTokenKind::IDENTIFIER,
          text ) );
  }

  return *( new ConstantToken( start, text ) );
}

Token & Lexer::readCharacterConstant()
{
  /*
   * Character CONSTANT
   */
  Pos start(pos);
  std::string text = "";
  text += file.get();

  unsigned length = 0;
  bool illegalEscapeSequence = false;
  bool newLine = false;

  while ( file.good() && file.peek() != '\'' )
  {
    if ( file.peek() == '\n' || file.peek() == '\r' )
    {
      newLine = true;
      break;
    }
    else if ( file.peek() == '\\' )
    {
      // Escape Sequence
      text += file.get();

      switch ( file.peek() )
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
          illegalEscapeSequence = true;
      }
    }
    text += file.get();
    ++length;
  }
  
  if ( length > 1 )
  {
    return *( new IllegalToken( start,
          IllegalTokenKind::CONSTANT_MULTIPLE_CHARACTERS, text ) );
  }
  else if ( illegalEscapeSequence )
  {
    return *( new IllegalToken( start, IllegalTokenKind::ESCAPE_SEQUENCE,
          text ) );
  }

  return *( new ConstantToken( start, text ) );
}


void Lexer::skip()
{
  int c;
  if ( file.good() )
  {
    c = file.get();
    updatePos( c );
  }

  while ( file.good() )
  {
    c = file.peek();

    if ( isspace( c ) )
    {
      file.get();
      updatePos( c );
      continue;
    }
    else if ( c == '\\' )
    {
      file.get();
      if ( file.peek() == '\n' )
      {
        // escaped newline
        continue;
      }
      else
      {
        // non-whitespace
        file.unget();
        break;
      }
    }
    else if ( c == '/' )
    {
      file.get();
      if ( file.peek() == '/' )
      {
        // comment line
        updatePos( c );
        while ( c == '\\' || file.peek() != '\n' )
        {
          c = file.get();
          updatePos( c );
        }
        continue;
      }
      else if ( file.peek() == '*' )
      {
        // comment block
        updatePos( c );
        file.get(); // read the *
        updatePos( c );
        c = file.get(); // read the next char, skip previous * to prevent /*/
        updatePos( c );

        if ( ! file.good() )
          return;

        while ( c != '*' || file.peek() != '/' )
        {
          c = file.get();
          updatePos( c );
        }

        c = file.get(); // read last /
        updatePos( c );

        continue;
      }
      else
      {
        // non-whitespace
        file.unget(); // wrte back the /
        break;
      }
    }
    else
      // non-whitespace
      break;
  }
}

void Lexer::updatePos( int c )
{
  if ( c == '\n' )
  {
    ++pos.line;
    pos.column = 1;
  }
  else
    ++pos.column;
}
