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

Token & Lexer::get()
{
  if ( ! file.good() )
    return *( new EofToken( pos ) );

  Token &t = skip();
  
  // Hack for the unterminated comment block
  if ( t.kind != TokenKind::END_OF_FILE )
    return t;

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
  else if ( file.peek() == '\'' || file.peek() == '"' )
  {
    // Character Constant or String Literal
    return readCharacterConstantOrStringLiteral();
  }
  else
  {
    // Punctuator
    return readPunctuator();
  }
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

  if ( ! file.good() || ! ( isalpha( file.peek() ) || file.peek() == '_' ) )
  {
    // read first character
    updatePos( file.peek() );
    text += file.get();

    return *( new IllegalToken( start, IllegalTokenKind::IDENTIFIER, text ) );
  }

  while ( file.good() && ( isalnum( file.peek() ) || file.peek() == '_' ) )
  {
    updatePos( file.peek() );
    text += file.get();
  }

  auto it = Keywords.find( text ) ;
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

  bool isIllegalIdentifier = false;

  // Hex and Oct support
  bool isHex = false;
  bool isOct = false;
  if ( file.peek() == '0' )
  {
    updatePos( file.peek() );
    text += file.get();
    if ( file.peek() == 'x' || file.peek() == 'X' )
    {
      isHex = true;
      updatePos( file.peek() );
      text += file.get();

      if ( ! isxdigit( file.peek() ) )
        isIllegalIdentifier = true;
    }
    else
      isOct = true;
  }

  while ( file.good() )
  {
    if ( isHex )
    {
      if ( ! isxdigit( file.peek() ) )
        break;
    }
    else if ( isOct )
    {
      if ( ! ( '0' <= file.peek() && file.peek() < '8' ) )
        break;
    }
    else if ( ! isdigit( file.peek() ) )
      break;

    updatePos( file.peek() );
    text += file.get();
  }

  // support for 1u 1U 1l 1L 1ll 1LL
  bool isLong = false;
  bool isUnsigned = false;
  while ( file.good() && ( isalnum( file.peek() ) || file.peek() == '_' ) )
  {
    if ( ! isIllegalIdentifier )
    {
      // 1u 1U
      if ( ! isUnsigned && ( file.peek() == 'u' || file.peek() == 'U' ) )
      {
        isUnsigned = true;
        updatePos( file.peek() );
        text += file.get();
        continue;
      }
      // 1l 1L 1ll 1LL
      else if ( ! isLong && ( file.peek() == 'l' || file.peek() == 'L' ) )
      {
        isLong = true;
        char suf = file.peek();
        updatePos( file.peek() );
        text += file.get();

        // 1ll 1LL
        if ( file.peek() == suf )
        {
          updatePos( file.peek() );
          text += file.get();
        }

        continue;
      }
      else
        isIllegalIdentifier = true;
    }

    updatePos( file.peek() );
    text += file.get();
  }

  if ( isIllegalIdentifier )
  {
    // ILLEGAL Identifier
    return *( new IllegalToken( start, IllegalTokenKind::IDENTIFIER,
          text ) );
  }

  return *( new ConstantToken( start, text ) );
}

Token & Lexer::readCharacterConstantOrStringLiteral()
{
  /*
   * Character CONSTANT or STRING LITERAL
   */
  Pos start(pos);
  std::string text = "";

  int terminator = file.peek();
  bool isCharConst = terminator == '\'';

  // read first character
  updatePos( file.peek() );
  text += file.get();

  unsigned length = 0;
  bool illegalEscapeSequence = false;
  bool newLine = false;

  while ( file.good() && file.peek() != terminator )
  {
    if ( file.peek() == '\n' )
    {
      newLine = true;
      break;
    }
    else if ( file.peek() == '\\' )
    {
      // Escape Sequence
      updatePos( file.peek() );
      text += file.get();

      switch ( file.peek() )
      {
				case '0':
        case '"':
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
    updatePos( file.peek() );
    text += file.get();
    ++length;
  }

  if ( file.peek() == terminator )
  {
    // read terminating apostrophe or quote
    updatePos( file.peek() );
    text += file.get();
  }

	if ( isCharConst && length == 0 )
		return *( new IllegalToken( start,
					IllegalTokenKind::EMPTY_CHARACTER_CONSTANT, text ) );
  if ( isCharConst && length > 1 )
  {
    return *( new IllegalToken( start,
          IllegalTokenKind::CONSTANT_MULTIPLE_CHARACTERS, text ) );
  }
  else if ( newLine )
  {
    return *( new IllegalToken( start,
          ( isCharConst ? IllegalTokenKind::MISSING_APOSTROPHE :
            IllegalTokenKind::MISSING_QUOTE ),
          text ) );
  }
  else if ( illegalEscapeSequence )
  {
    return *( new IllegalToken( start, IllegalTokenKind::ESCAPE_SEQUENCE,
          text ) );
  }

  if ( isCharConst )
    return *( new ConstantToken( start, text ) );
  return *( new StringLiteralToken( start, text ) );
}

Token & Lexer::readPunctuator()
{
  /*
   * Punctuator
   */
  Pos start(pos);
  std::string text = "";

#define PUNCTUATOR( kind ) \
  return *( new PunctuatorToken( start, ( kind ), text ) );

#define PUNCTUATOR_GET( kind ) \
  { \
  updatePos( file.peek() ); \
  text += file.get(); \
  PUNCTUATOR( kind ); \
  }

#define PUNCTUATOR_GET_IF( chr, kind ) \
  if ( file.peek() == ( chr ) ) \
  PUNCTUATOR_GET( kind );


  switch ( file.peek() )
  {
    // Punctuators that consist of a single character
    case '(':
      PUNCTUATOR_GET( PunctuatorKind::LPAR );
    case ')':
      PUNCTUATOR_GET( PunctuatorKind::RPAR );
    case ',':
      PUNCTUATOR_GET( PunctuatorKind::COMMA );
    case ';':
      PUNCTUATOR_GET( PunctuatorKind::SEMICOLON );
    case '?':
      PUNCTUATOR_GET( PunctuatorKind::QMARK );
    case '[':
      PUNCTUATOR_GET( PunctuatorKind::LBRACKET );
    case ']':
      PUNCTUATOR_GET( PunctuatorKind::RBRACKET );
    case '{':
      PUNCTUATOR_GET( PunctuatorKind::LBRACE );
    case '}':
      PUNCTUATOR_GET( PunctuatorKind::RBRACE );
    case '~':
      PUNCTUATOR_GET( PunctuatorKind::NEG );

      // Punctuators that can have more than one character
    case ':':
      updatePos( file.peek() );
      text += file.get();

      // :>
      PUNCTUATOR_GET_IF( '>', PunctuatorKind::RBRACKET );
      // :
      PUNCTUATOR( PunctuatorKind::COLON );

    case '!':
      updatePos( file.peek() );
      text += file.get();

      PUNCTUATOR_GET_IF( '=', PunctuatorKind::NE );
      PUNCTUATOR( PunctuatorKind::NOT );

    case '#':
      updatePos( file.peek() );
      text += file.get();

      PUNCTUATOR_GET_IF( '#', PunctuatorKind::DHASH );
      PUNCTUATOR( PunctuatorKind::HASH );

    case '%':
      updatePos( file.peek() );
      text += file.get();

      // %=
      PUNCTUATOR_GET_IF( '=', PunctuatorKind::MODASSIGN );
      // %>
      PUNCTUATOR_GET_IF( '>', PunctuatorKind::RBRACE );
      // %:
      if ( file.peek() == ':' )
      {
        updatePos( file.peek() );
        text += file.get();

        if ( file.peek() == '%' )
        {
          updatePos( file.peek() );
          text += file.get();

          // %:%:
          PUNCTUATOR_GET_IF( ':', PunctuatorKind::DHASH );

          file.unget();
        }
        PUNCTUATOR( PunctuatorKind::HASH );
      }
      // %
      PUNCTUATOR( PunctuatorKind::MOD );

    case '&':
      updatePos( file.peek() );
      text += file.get();

      PUNCTUATOR_GET_IF( '&', PunctuatorKind::LAND );
      PUNCTUATOR_GET_IF( '=', PunctuatorKind::ANDASSIGN );
      PUNCTUATOR( PunctuatorKind::AND );

    case '*':
      updatePos( file.peek() );
      text += file.get();

      PUNCTUATOR_GET_IF( '=', PunctuatorKind::MULASSIGN );
      PUNCTUATOR( PunctuatorKind::MUL );

    case '+':
      updatePos( file.peek() );
      text += file.get();

      PUNCTUATOR_GET_IF( '+', PunctuatorKind::INC );
      PUNCTUATOR_GET_IF( '=', PunctuatorKind::ADDASSIGN );
      PUNCTUATOR( PunctuatorKind::PLUS );

    case '-':
      updatePos( file.peek() );
      text += file.get();

      PUNCTUATOR_GET_IF( '-', PunctuatorKind::DEC );
      PUNCTUATOR_GET_IF( '=', PunctuatorKind::SUBASSIGN );
      PUNCTUATOR_GET_IF( '>', PunctuatorKind::ARROW );
      PUNCTUATOR( PunctuatorKind::MINUS );

    case '.':
      updatePos( file.peek() );
      text += file.get();

      if ( file.peek() == '.' ) // 2nd .
      {
        file.get();
        if ( file.peek() == '.' ) // 3rd .
        {
          // ...
          updatePos( '.' );
          text += ".";
          PUNCTUATOR_GET( PunctuatorKind::ELLIPSIS );
        }
        // ..
        file.unget();
        PUNCTUATOR( PunctuatorKind::DOT );
      }
      // .
      PUNCTUATOR( PunctuatorKind::DOT );

    case '/':
      updatePos( file.peek() );
      text += file.get();

      PUNCTUATOR_GET_IF( '=', PunctuatorKind::DIVASSIGN );
      PUNCTUATOR( PunctuatorKind::DIV );

    case '<':
      updatePos( file.peek() );
      text += file.get();

      // <=
      PUNCTUATOR_GET_IF( '=', PunctuatorKind::LEQ );
      // <:
      PUNCTUATOR_GET_IF( ':', PunctuatorKind::LBRACKET );
      // <%
      PUNCTUATOR_GET_IF( '%', PunctuatorKind::LBRACE );
      // <<
      if ( file.peek() == '<' )
      {
        updatePos( file.peek() );
        text += file.get();

        // <<=
        PUNCTUATOR_GET_IF( '=', PunctuatorKind::LSHIFTASSIGN );
        // <<
        PUNCTUATOR( PunctuatorKind::LSHIFT );
      }
      // <
      PUNCTUATOR( PunctuatorKind::LE );

    case '=':
      updatePos( file.peek() );
      text += file.get();

      PUNCTUATOR_GET_IF( '=', PunctuatorKind::EQ );
      PUNCTUATOR( PunctuatorKind::ASSIGN );

    case '>':
      updatePos( file.peek() );
      text += file.get();

      // >=
      PUNCTUATOR_GET_IF( '=', PunctuatorKind::GEQ );
      if ( file.peek() == '>' )
      {
        updatePos( file.peek() );
        text += file.get();

        // >>=
        PUNCTUATOR_GET_IF( '=', PunctuatorKind::RSHIFTASSIGN );
        // >>
        PUNCTUATOR( PunctuatorKind::RSHIFT );
      }
      // >
      PUNCTUATOR( PunctuatorKind::GR );

    case '^':
      updatePos( file.peek() );
      text += file.get();

      PUNCTUATOR_GET_IF( '=', PunctuatorKind::XORASSIGN );
      PUNCTUATOR( PunctuatorKind::XOR );

    case '|':
      updatePos( file.peek() );
      text += file.get();

      PUNCTUATOR_GET_IF( '=', PunctuatorKind::ORASSIGN );
      PUNCTUATOR_GET_IF( '|', PunctuatorKind::LOR );
      PUNCTUATOR( PunctuatorKind::OR );

    default:
      // Illegal Punctuator
      updatePos( file.peek() );
      text += file.get();
      return *( new IllegalToken( start, IllegalTokenKind::UNKNOWN, text ) );
  }
}


Token & Lexer::skip()
{
  int c;
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
        while ( file.good() && ( c == '\\' || file.peek() != '\n' ) )
        {
          c = file.get();
          updatePos( c );
        }
        continue;
      }
      else if ( file.peek() == '*' )
      {
        // comment block
        Pos start( pos );
        updatePos( c );
        file.get(); // read the *

        updatePos( c );
        c = file.get(); // read the next char, skip previous * to prevent /*/

        while ( file.good() && ( c != '*' || file.peek() != '/' ) )
        {
          updatePos( c );
          c = file.get();
        }

        if ( ! file.good() )
          return *( new IllegalToken( start,
                IllegalTokenKind::MISSING_COMMENT_TERMINATOR, "" ) );

        c = file.get(); // read last /
        updatePos( c );

        continue;
      }
      else
      {
        // non-whitespace
        file.unget(); // write back the /
        break;
      }
    }
    else
      // non-whitespace
      break;
  }
  return *( new EofToken( pos ) );
}

void Lexer::step()
{
  updatePos( file.peek() );
  file.get();
}

void Lexer::updatePos( int c )
{
  if ( c == '\n' )
  {
    ++pos.line;
    pos.column = 1u;
  }
  else
    ++pos.column;
}
