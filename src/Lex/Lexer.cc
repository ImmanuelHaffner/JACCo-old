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
#include "IllegalToken.h"

using namespace C4;
using namespace Lex;

Lexer::Lexer() : fileName("<stdin>"), file( std::cin ), pos("<stdin>", 1, 1),
  cur(NULL), prev(NULL)
{}

Lexer::Lexer( char const * const fileName ) : fileName(fileName),
  file( * new std::ifstream( fileName ) ), pos(fileName, 1, 1), cur(NULL),
  prev(NULL)
{}

Lexer::Lexer( std::string const &fileName ) : fileName(fileName),
  file( * new std::ifstream( fileName ) ),
  pos(fileName.c_str(), 1, 1), cur(NULL), prev(NULL)
{}

Lexer::~Lexer()
{
  if ( prev )
    delete prev;
  if ( cur )
    delete cur;
}

Token & Lexer::get()
{
  if ( prev )
    delete prev;

  if ( cur )
  {
    prev = cur;
    cur = NULL;
    return prev->clone();
  }
  prev = & getToken();
  return prev->clone();
}

Token & Lexer::peek()
{
  if ( ! cur )
    cur = & getToken();
  return cur->clone();
}

void Lexer::unget()
{
  if ( prev )
  {
    if ( cur )
      delete cur;
    cur = prev;
    prev = NULL;
  }
}

Token & Lexer::getToken()
{
  if ( ! file.good() )
    return Token::EndOfFile( pos );

  Token &t = skip();
  
  // Hack for the unterminated comment block
  if ( t.kind != TokenKind::END_OF_FILE )
    return t;
  else
    delete &t;

  if ( ! file.good() )
    return Token::EndOfFile( pos );

  if ( isdigit( file.peek() ) )
  {
    // Numerical Constant
    return readNumericalConstant();
  }
  else if ( file.peek() == 'L' || file.peek() == 'u' || file.peek() == 'U' )
  {
    file.get();
    if ( file.peek() == '\'' || file.peek() == '"' )
    {
      file.unget();
      return readCharacterConstantOrStringLiteral();
    }
    file.unget();
    return readKeywordOrIdentifier();
  }
  else if ( isalpha( file.peek() ) || file.peek() == '_' )
  {
    // Keyword or Identifier
    return readKeywordOrIdentifier();
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
    return Token::Keyword( start, text );

  return Token::Identifier( start, text );
}

Token & Lexer::readNumericalConstant()
{
  /*
   * Numerical CONSTANT
   */
  Pos start( pos );
  std::string text = "";

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
        return *( new IllegalToken( start, IllegalTokenKind::HEX_CONSTANT,
              text ) );
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
  while ( file.good() && isalpha( file.peek() ) )
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
    break;
  }

  return Token::Constant( start, text );
}

Token & Lexer::readCharacterConstantOrStringLiteral()
{
  /*
   * Character CONSTANT or STRING LITERAL
   */
  Pos start(pos);
  std::string text = "";

  if ( file.peek() == 'L' || file.peek() == 'u' || file.peek() == 'U' )
  {
    updatePos( file.peek() );
    text += file.get();
  }

  assert( ( file.peek() == '\'' || file.peek() == '"' )
      && "quote or apostrophe expected" );

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
    // \r\n
    if ( file.peek() == '\r' )
    {
      newLine = true;
      file.get();
      if ( file.peek() != '\n' )
        file.unget();
      break;
    }
    // \n
    if ( file.peek() == '\n' )
    {
      newLine = true;
      break;
    }
    else if ( file.peek() == '\\' )
    {
      int c = file.get();
      // \r\n
      if ( file.peek() == '\r' )
      {
        file.get();
        if ( file.peek() != '\n' )
          file.unget();
        // escaped newline
        updatePos( file.get() );
        continue;
      }
      // \n
      if ( file.peek() == '\n' )
      {
        // escaped newline
        updatePos( file.get() );
        continue;
      }

      // Escape Sequence
      updatePos( c );
      text += c;

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
    return Token::Constant( start, text );
  return Token::StringLiteral( start, text );
}

Token & Lexer::readPunctuator()
{
  /*
   * Punctuator
   */
  Pos start(pos);
  std::string text = "";

#define GET \
  updatePos( file.peek() ); \
  text += file.get();

#define GET_IF( chr ) \
  if ( file.peek() == ( chr ) ) \
  {\
    GET; \
  }

#define PUNCTUATOR_GET_IF( chr ) \
  if ( file.peek() == ( chr ) ) \
  { \
    GET; \
    return Token::Punctuator( start, text ); \
  }

  switch ( file.peek() )
  {
    // Punctuators that consist of a single character
    case '(':
    case ')':
    case ',':
    case ';':
    case '?':
    case '[':
    case ']':
    case '{':
    case '}':
    case '~':
      GET;
      return Token::Punctuator( start, text );

      //
      // Punctuators that can have more than one character
      //

    case ':':
      GET;
      // :>
      GET_IF( '>' );
      // :
      return Token::Punctuator( start, text );

    case '!':
      GET;
      // !=
      GET_IF( '=' );
      return Token::Punctuator( start, text );

    case '#':
      GET;
      // ##
      GET_IF ( '#' );
      return Token::Punctuator( start, text );

    case '%':
      GET;

      // %=
      PUNCTUATOR_GET_IF( '=' );
      // %>
      PUNCTUATOR_GET_IF( '>' );
      // %:
      if ( file.peek() == ':' )
      {
        GET;

        if ( file.peek() == '%' )
        {
          file.get();

          if ( file.peek() == ':' )
          {
            updatePos( '%' );
            text += "%";
            GET;
            return Token::Punctuator( start, text );
          }

          file.unget();
        }
        return Token::Punctuator( start, text );
      }
      // %
      return Token::Punctuator( start, text );

    case '&':
      GET;

      PUNCTUATOR_GET_IF( '&' );
      PUNCTUATOR_GET_IF( '=' );
      return Token::Punctuator( start, text );

    case '*':
      GET;

      PUNCTUATOR_GET_IF( '=' );
      return Token::Punctuator( start, text );

    case '+':
      GET;

      PUNCTUATOR_GET_IF( '+' );
      PUNCTUATOR_GET_IF( '=' );
      return Token::Punctuator( start, text );

    case '-':
      GET;

      PUNCTUATOR_GET_IF( '-' );
      PUNCTUATOR_GET_IF( '=' );
      PUNCTUATOR_GET_IF( '>' );
      return Token::Punctuator( start, text );

    case '.':
      GET;

      if ( file.peek() == '.' ) // 2nd .
      {
        file.get();
        if ( file.peek() == '.' ) // 3rd .
        {
          // ...
          updatePos( '.' );
          text += '.';
          GET;
          return Token::Punctuator( start, text );
        }
        // ..
        file.unget();
        return Token::Punctuator( start, text );
      }
      // .
      return Token::Punctuator( start, text );

    case '/':
      GET;

      PUNCTUATOR_GET_IF( '=' );
      return Token::Punctuator( start, text );

    case '<':
      GET;

      // <=
      PUNCTUATOR_GET_IF( '=' );
      // <:
      PUNCTUATOR_GET_IF( ':' );
      // <%
      PUNCTUATOR_GET_IF( '%' );
      // <<
      if ( file.peek() == '<' )
      {
        GET;

        // <<=
        PUNCTUATOR_GET_IF( '=' );
        // <<
        return Token::Punctuator( start, text );
      }
      // <
      return Token::Punctuator( start, text );

    case '=':
      GET;

      PUNCTUATOR_GET_IF( '=' );
      return Token::Punctuator( start, text );

    case '>':
      GET;

      // >=
      PUNCTUATOR_GET_IF( '=' );
      if ( file.peek() == '>' )
      {
        GET;

        // >>=
        PUNCTUATOR_GET_IF( '=' );
        // >>
        return Token::Punctuator( start, text );
      }
      // >
      return Token::Punctuator( start, text );

    case '^':
      GET;

      PUNCTUATOR_GET_IF( '=' );
      return Token::Punctuator( start, text );

    case '|':
      GET;

      PUNCTUATOR_GET_IF( '=' );
      PUNCTUATOR_GET_IF( '|' );
      return Token::Punctuator( start, text );

    default:
      // Illegal Punctuator
      GET;
      return *( new IllegalToken( start, IllegalTokenKind::UNKNOWN, text ) );
  }
}

Token & Lexer::skip()
{
  int c;
  while ( file.good() )
  {
    if ( file.peek() == '\r' )
    {
      file.get();
      if ( file.peek() != '\n' )
        file.unget();
    }

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
      // \r\n
      if ( file.peek() == '\r' )
      {
        file.get();
        if ( file.peek() != '\n' )
          file.unget();
        // escaped newline
        continue;
      }
      // \n
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
        while ( file.good() && file.peek() != -1 )
        {
          if ( c != '\\' )
          {
            // \n
            if ( file.peek() == '\n' )
              break;
            // \r\n
            if ( file.peek() == '\r' )
            {
              file.get();
              if ( file.peek() != '\n' )
                file.unget();
              break;
            }
          }
          c = file.get();
          updatePos( c );
        }
        continue;
      }
      else if ( file.peek() == '*' )
      {
        // comment block
        Pos start( pos );

        updatePos( c ); // handle /
        c = file.get(); // read the *
        updatePos( c );

        // read the next char, skip previous * to prevent /*/
        // \r\n
        if ( file.peek() == '\r' )
        {
          file.get();
          if ( file.peek() != '\n' )
            file.unget();
        }
        updatePos( file.get() );

        while ( file.good() && file.peek() != -1
            && ( c != '*' || file.peek() != '/' ) )
        {
          // \r\n
          if ( file.peek() == '\r' )
          {
            file.get();
            if ( file.peek() != '\n' )
              file.unget();
          }
          c = file.get();
          updatePos( c );
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
  return Token::EndOfFile( pos );
}

void Lexer::step()
{
  updatePos( file.peek() );
  file.get();
}

void Lexer::updatePos( int c )
{
  if ( c == -1 )
    return;

  if ( c == '\n' || c == '\r' )
  {
    ++pos.line;
    pos.column = 1u;
  }
  else
    ++pos.column;
}
