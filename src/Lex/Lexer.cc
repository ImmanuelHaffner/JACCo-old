//===--- Lexer.cc ---------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements the Lexer interface.
//
//===----------------------------------------------------------------------===//

#include "Lexer.h"

#include <cctype>
#include "IllegalToken.h"

using namespace C4;
using namespace Lex;


Lexer::Lexer() : fileName( "<stdin>" ), pos( "<stdin>", 1, 1 ),
  file( *( new RegularFile() ) )
{}

Lexer::Lexer( std::string const &fileName ) : Lexer( fileName.c_str() )
{}

Lexer::Lexer( char const * const fileName ) : fileName( fileName ),
  pos( fileName, 1, 1 ), file( *( new MemMapFile( fileName ) ) )
{}

Lexer::~Lexer()
{
  delete &file;
}

Pos Lexer::getPos() const
{
  return Pos( this->pos );
}

Token & Lexer::getToken()
{
  while ( isspace( file.peek() ) )
    updatePos( file.get() );

  Pos start( pos );

  int c = updatePos( file.get() );

  if ( c == -1 )
    return Token::EndOfFile( pos );

  /*
   * 
   * Decide what to lex.
   *
   */

  //
  //  Character Constant or String Literal
  //
  if ( c == '\'' || c == '"'
      || ( ( c == 'L' || c == 'u' || c == 'U' )
        && ( file.peek() == '\'' || file.peek() == '"' ) ) )
  {
    std::string str;
    str += c;

    if ( c == 'L' || c == 'u' || c == 'U' )
      c = updatePos( file.get() );

    int terminator = c;
    bool isCharConst = terminator == '\'';

    if ( isCharConst && file.peek() == '\'' )
    {
      str += updatePos( file.get() );
      return *( new IllegalToken( start,
            IllegalTokenKind::EMPTY_CHARACTER_CONSTANT, str ) );
    }

    bool illegalEscapeSequence = false;
    unsigned length = 0;

    while ( file.peek() != terminator && file.peek() != -1 )
    {
      switch ( file.peek() )
      {
        // new line
        case '\n':
          updatePos( file.get() );
          goto NEWLINE;

          // escape sequence
        case '\\':
            str += updatePos( file.get() );
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

        default:
            ++length;
            str += updatePos( file.get() );
      }
    }

    if ( file.peek() == terminator )
      str += updatePos( file.get() );

    if ( isCharConst && length != 1 )
      return *( new IllegalToken( start,
            IllegalTokenKind::CONSTANT_MULTIPLE_CHARACTERS, str ) );

    if ( illegalEscapeSequence )
      return *( new IllegalToken( start, IllegalTokenKind::ESCAPE_SEQUENCE,
            str ) );

    if ( isCharConst )
      return Token::Constant( start, str );
    return Token::StringLiteral( start, str );

NEWLINE:
    return *( new IllegalToken( start,
          ( isCharConst ? IllegalTokenKind::MISSING_APOSTROPHE
            : IllegalTokenKind::MISSING_QUOTE ), str ) );
  }
  //
  //  Keyword or Identifier
  //
  else if ( isalpha( c ) || c == '_' )
  {
    std::string str;
    str += c;
    while ( isalnum( file.peek() ) || file.peek() == '_' )
    {
      str += updatePos( file.get() );
    }

    auto it = Keywords.find( str ) ;
    if ( it != Keywords.end() )
      return Token::Keyword( start, str );

    return Token::Identifier( start, str );
  }
  //
  //  Numerical Constant
  //
  else if ( isdigit( c ) )
  {
    std::string str;
    str += c;
    bool isHex = false, isOct = false;

    //
    //  Check whether the number is hex, oct or decimal
    //
    if ( c == '0' )
    {
      if ( file.peek() == 'x' || file.peek() == 'X' ) // 0x OR 0X
      {
        str += c = updatePos( file.get() );  // c = x OR c = X
        // 0x must be followed by a hexadecimal digit
        if ( ! isxdigit( file.peek() ) )
          return *( new IllegalToken( start, IllegalTokenKind::HEX_CONSTANT,
                str ) );
        isHex = true;
      }
      else                        // 0 only
        isOct = true;
    }

    //
    //  Lex Octal Numerical Constant
    //
    if ( isOct )
    {
      while ( '0' <= file.peek() && file.peek() < '8' )
        str += updatePos( file.get() );
    }
    //
    //  Lex Hexadecimal Numerical Constant
    //
    else if ( isHex )
    {
      while ( isxdigit( file.peek() ) )
        str += updatePos( file.get() );
    }
    //
    //  Lex Decimal Numerical Constant
    //
    else
    {
      while ( isdigit( file.peek() ) )
        str += updatePos( file.get() );
    }

    //
    //  Lex Integer Suffix
    //
    bool isLong = false;
    bool isUnsigned = false;

    while ( true )
    {
      switch ( file.peek() )
      {
        case 'u':
        case 'U':
          if ( isUnsigned )
            goto end;
          isUnsigned = true;
          str += updatePos( file.get() );
          break;

        case 'l':
        case 'L':
          {
            if ( isLong )
              goto end;
            isLong = true;
            int l = updatePos( file.get() );
            str += l;
            if ( file.peek() == l )
              str += updatePos( file.get() );
            break;
          }

        default:
          goto end;
      }
    }
end:
    return Token::Constant( start, str );
  }
  //
  //  Punctuator
  //
  else
  {
    switch ( c )
    {
      // Punctuators that consist of a single character
      case '(':
        return Token::Punctuator( start, "(" );
      case ')':
        return Token::Punctuator( start, ")" );
      case ',':
        return Token::Punctuator( start, "," );
      case ';':
        return Token::Punctuator( start, ";" );
      case '?':
        return Token::Punctuator( start, "?" );
      case '[':
        return Token::Punctuator( start, "[" );
      case ']':
        return Token::Punctuator( start, "]" );
      case '{':
        return Token::Punctuator( start, "{" );
      case '}':
        return Token::Punctuator( start, "}" );
      case '~':
        return Token::Punctuator( start, "~" );

        //
        // Punctuators that can have more than one character
        //

      case ':':
        switch ( file.peek() )
        {
          // :>
          case '>':
            updatePos( file.get() );
            return Token::Punctuator( start, ":>" );

            // :
          default:
            return Token::Punctuator( start, ":" );
        }

      case '!':
        switch ( file.peek() )
        {
          // !=
          case '=':
            updatePos( file.get() );
            return Token::Punctuator( start, "!=" );

            // !
          default:
            return Token::Punctuator( start, "!" );
        }

      case '#':
        switch ( file.peek() )
        {
          // ##
          case '#':
            updatePos( file.get() );
            return Token::Punctuator( start, "##" );

            // #
          default:
            return Token::Punctuator( start, "#" );
        }

      case '%':
        switch ( file.peek() )
        {
          // %=
          case '=':
            updatePos( file.get() );
            return Token::Punctuator( start, "%=" );

            // %>
          case '>':
            updatePos( file.get() );
            return Token::Punctuator( start, "%>" );

            // %:
          case ':':
            {
              updatePos( file.get() );
              if ( file.peek() == '%' && file.peek( 1 ) == ':' )
              {
                // %:%:
                updatePos( file.get() );
                updatePos( file.get() );
                return Token::Punctuator( start, "%:%:" );
              }
              return Token::Punctuator( start, "%:" );
            }

            // %
          default:
            return Token::Punctuator( start, "%" );
        }

      case '&':
        switch ( file.peek() )
        {
          // &&
          case '&':
            updatePos( file.get() );
            return Token::Punctuator( start, "&&" );

            // &=
          case '=':
            updatePos( file.get() );
            return Token::Punctuator( start, "&=" );

            // &
          default:
            return Token::Punctuator( start, "&" );
        }

      case '*':
        switch ( file.peek() )
        {
          case '=':
            updatePos( file.get() );
            return Token::Punctuator( start, "*=" );

          default:
            return Token::Punctuator( start, "*" );
        }

      case '+':
        switch ( file.peek() )
        {
          // ++
          case '+':
            updatePos( file.get() );
            return Token::Punctuator( start, "++" );

            // +=
          case '=':
            updatePos( file.get() );
            return Token::Punctuator( start, "+=" );

            // +
          default:
            return Token::Punctuator( start, "+" );
        }

      case '-':
        switch ( file.peek() )
        {
          // --
          case '-':
            updatePos( file.get() );
            return Token::Punctuator( start, "--" );

          case '=':
            updatePos( file.get() );
            return Token::Punctuator( start, "-=" );

          case '>':
            updatePos( file.get() );
            return Token::Punctuator( start, "->" );

            // -
          default:
            return Token::Punctuator( start, "-" );
        }

      case '.':
        switch ( file.peek() )
        {
          // ..
          case '.':
            {
              if ( file.peek( 1 ) == '.' )
              {
                // ...
                updatePos( file.get() );
                updatePos( file.get() );
                return Token::Punctuator( start, "..." );
              }
            }

            // .
          default:
            return Token::Punctuator( start, "." );
        }

      case '/':
        switch ( file.peek() )
        {
          // /=
          case '=':
            updatePos( file.get() );
            return Token::Punctuator( start, "/=" );

            // /
          default:
            return Token::Punctuator( start, "/" );
        }

      case '<':
        switch ( file.peek() )
        {
          // <=
          case '=':
            updatePos( file.get() );
            return Token::Punctuator( start, "<=" );

          // <:
          case ':':
            updatePos( file.get() );
            return Token::Punctuator( start, "<:" );

          // <%
          case '%':
            updatePos( file.get() );
            return Token::Punctuator( start, "<%" );

            // <<
          case '<':
            updatePos( file.get() );
            if ( file.peek() == '=' )
            {
              // <<=
              updatePos( file.get() );
              return Token::Punctuator( start, "<<=" );
            }
            return Token::Punctuator( start, "<<" );

            // <
          default:
            return Token::Punctuator( start, "<" );
        }

      case '=':
        switch ( file.peek() )
        {
          // ==
          case '=':
            updatePos( file.get() );
            return Token::Punctuator( start, "==" );

            // =
          default:
            return Token::Punctuator( start, "=" );
        }

      case '>':
        switch ( file.peek() )
        {
          // >=
          case '=':
            updatePos( file.get() );
            return Token::Punctuator( start, ">=" );

            // >>
          case '>':
            updatePos( file.get() );
            if ( file.peek() == '=' )
            {
              // >>=
              updatePos( file.get() );
              return Token::Punctuator( start, ">>=" );
            }
            return Token::Punctuator( start, ">>" );

            // >
          default:
            return Token::Punctuator( start, ">" );
        }

      case '^':
        switch ( file.peek() )
        {
          // ^=
          case '=':
            updatePos( file.get() );
            return Token::Punctuator( start, "^=" );

            // ^
          default:
            return Token::Punctuator( start, "^" );
        }

      case '|':
        switch ( file.peek() )
        {
          // |=
          case '=':
            updatePos( file.get() );
            return Token::Punctuator( start, "|=" );

          // ||
          case '|':
            updatePos( file.get() );
            return Token::Punctuator( start, "||" );

            // |
          default:
            return Token::Punctuator( start, "|" );
        }


      default:
        // Illegal Punctuator
        std::string str;
        str += updatePos( file.get() );
        return *( new IllegalToken( start, IllegalTokenKind::UNKNOWN, str ) );
    }
  }
}
