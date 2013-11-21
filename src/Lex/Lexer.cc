//===--- Lexer.cc ---------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements the Lexer interface.
//
//===----------------------------------------------------------------------===//

#include "Lexer.h"

#include <cctype>
#include "../diagnostic.h"

using namespace C4;
using namespace Lex;


Lexer::Lexer() : fileName( "<stdin>" ), pos( "<stdin>", 1, 0 ),
  file( *( new RegularFile() ) )
{}

Lexer::Lexer( std::string const &fileName ) : Lexer( fileName.c_str() )
{}

Lexer::Lexer( char const * const fileName ) : fileName( fileName ),
  pos( fileName, 1, 0 ), file( *( new MemMapFile( fileName ) ) )
{}

Lexer::~Lexer()
{
  delete &file;
}

Pos Lexer::getPos() const
{
  return Pos( this->pos );
}

Token Lexer::getToken()
{
  buf.clear();

  for (;;)
  {
    switch ( c )
    {
      case -1:
        nextChar();
        // check whether we continue after an eof, for testing only
        if ( c == -1 )
          return Token::EndOfFile( pos );
        else
          continue;

      case ' ':
      case '\t':
      case '\n':
      case '\v':
      case '\f':
        nextChar();
        continue;

      case '\'':
      case '"':
        return lexCharConstOrStringLiteral();

      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
        return lexNumericalConstant();

      default:;
    } // end switch

    Pos start( pos );
    switch ( c )
    {

      case '(':
        nextChar();
        return Token::Punctuator( start, TK::LPar, "(" );
      case ')':
        nextChar();
        return Token::Punctuator( start, TK::RPar, ")" );
      case ',':
        nextChar();
        return Token::Punctuator( start, TK::Comma, "," );
      case ';':
        nextChar();
        return Token::Punctuator( start, TK::SCol, ";" );
      case '?':
        nextChar();
        return Token::Punctuator( start, TK::QMark, "?" );
      case '[':
        nextChar();
        return Token::Punctuator( start, TK::LBracket, "[" );
      case ']':
        nextChar();
        return Token::Punctuator( start, TK::RBracket, "]" );
      case '{':
        nextChar();
        return Token::Punctuator( start, TK::LBrace, "{" );
      case '}':
        nextChar();
        return Token::Punctuator( start, TK::RBrace, "}" );
      case '~':
        nextChar();
        return Token::Punctuator( start, TK::Neg, "~" );

        //
        // Punctuators that can have more than one character
        //

      case ':':
        nextChar();
        switch ( c )
        {
          // :>
          case '>':
            nextChar();
            return Token::Punctuator( start, TK::RBracket, ":>" );

            // :
          default:
            return Token::Punctuator( start, TK::Col, ":" );
        }

      case '!':
        nextChar();
        switch ( c )
        {
          // !=
          case '=':
            nextChar();
            return Token::Punctuator( start, TK::NE, "!=" );

            // !
          default:
            return Token::Punctuator( start, TK::Not, "!" );
        }

      case '#':
        nextChar();
        switch ( c )
        {
          // ##
          case '#':
            nextChar();
            return Token::Punctuator( start, TK::DHash, "##" );

            // #
          default:
            return Token::Punctuator( start, TK::Hash, "#" );
        }

      case '%':
        nextChar();
        switch ( c )
        {
          // %=
          case '=':
            nextChar();
            return Token::Punctuator( start, TK::ModAssign, "%=" );

            // %>
          case '>':
            nextChar();
            return Token::Punctuator( start, TK::RBrace, "%>" );

            // %:
          case ':':
            {
              nextChar();
              if ( c == '%' && file.peek() == ':' )
              {
                // %:%:
                nextChar();
                nextChar();
                return Token::Punctuator( start, TK::DHash, "%:%:" );
              }
              // %:
              return Token::Punctuator( start, TK::Hash, "%:" );
            }

            // %
          default:
            return Token::Punctuator( start, TK::Mod, "%" );
        }

      case '&':
        nextChar();
        switch ( c )
        {
          // &&
          case '&':
            nextChar();
            return Token::Punctuator( start, TK::LAnd, "&&" );

            // &=
          case '=':
            nextChar();
            return Token::Punctuator( start, TK::AndAssign, "&=" );

            // &
          default:
            return Token::Punctuator( start, TK::And, "&" );
        }

      case '*':
        nextChar();
        switch ( c )
        {
          case '=':
            nextChar();
            return Token::Punctuator( start, TK::MulAssign, "*=" );

          default:
            return Token::Punctuator( start, TK::Mul, "*" );
        }

      case '+':
        nextChar();
        switch ( c )
        {
          // ++
          case '+':
            nextChar();
            return Token::Punctuator( start, TK::IncOp, "++" );

            // +=
          case '=':
            nextChar();
            return Token::Punctuator( start, TK::AddAssign, "+=" );

            // +
          default:
            return Token::Punctuator( start, TK::Plus, "+" );
        }

      case '-':
        nextChar();
        switch ( c )
        {
          // --
          case '-':
            nextChar();
            return Token::Punctuator( start, TK::DecOp, "--" );

          case '=':
            nextChar();
            return Token::Punctuator( start, TK::SubAssign, "-=" );

          case '>':
            nextChar();
            return Token::Punctuator( start, TK::PtrOp, "->" );

            // -
          default:
            return Token::Punctuator( start, TK::Minus, "-" );
        }

      case '.':
        nextChar();
        switch ( c )
        {
          // ..
          case '.':
            if ( file.peek() == '.' )
            {
              // ...
              nextChar();
              nextChar();
              return Token::Punctuator( start, TK::Ellipsis, "..." );
            }

            // .
          default:
            return Token::Punctuator( start, TK::Dot, "." );
        }

      case '<':
        nextChar();
        switch ( c )
        {
          // <=
          case '=':
            nextChar();
            return Token::Punctuator( start, TK::LEq, "<=" );

            // <:
          case ':':
            nextChar();
            return Token::Punctuator( start, TK::LBracket, "<:" );

            // <%
          case '%':
            nextChar();
            return Token::Punctuator( start, TK::LBrace, "<%" );

            // <<
          case '<':
            nextChar();
            if ( c == '=' )
            {
              // <<=
              nextChar();
              return Token::Punctuator( start, TK::LShiftAssign, "<<=" );
            }
            // <<
            return Token::Punctuator( start, TK::LShift, "<<" );

            // <
          default:
            return Token::Punctuator( start, TK::Le, "<" );
        }

      case '=':
        nextChar();
        switch ( c )
        {
          // ==
          case '=':
            nextChar();
            return Token::Punctuator( start, TK::Eq, "==" );

            // =
          default:
            return Token::Punctuator( start, TK::Assign, "=" );
        }

      case '>':
        nextChar();
        switch ( c )
        {
          // >=
          case '=':
            nextChar();
            return Token::Punctuator( start, TK::GEq, ">=" );

            // >>
          case '>':
            nextChar();
            if ( c == '=' )
            {
              // >>=
              nextChar();
              return Token::Punctuator( start, TK::RShiftAssign, ">>=" );
            }
            // >>
            return Token::Punctuator( start, TK::RShift, ">>" );

            // >
          default:
            return Token::Punctuator( start, TK::Gr, ">" );
        }

      case '^':
        nextChar();
        switch ( c )
        {
          // ^=
          case '=':
            nextChar();
            return Token::Punctuator( start, TK::XorAssign, "^=" );

            // ^
          default:
            return Token::Punctuator( start, TK::Xor, "^" );
        }

      case '|':
        nextChar();
        switch ( c )
        {
          // |=
          case '=':
            nextChar();
            return Token::Punctuator( start, TK::OrAssign, "|=" );

            // ||
          case '|':
            nextChar();
            return Token::Punctuator( start, TK::LOr, "||" );

            // |
          default:
            return Token::Punctuator( start, TK::Or, "|" );
        }

      case '/':
        nextChar();
        switch ( c )
        {
          //
          //  Comments
          //

            // Comment-line
          case '/':
            do
              nextChar();
            while ( c != -1 && c != '\n' );
            continue;

            // Comment-block
          case '*':
            // read * to handle /*/
            do
              nextChar();
            while ( c != -1 && ! ( c == '*' && file.peek() == '/' ) );
            if ( c == -1 )
              errorf( start, "%s", "unterminated comment block" );
            else
            {
              nextChar();
              nextChar();
            }
            continue;

          // /=
          case '=':
            nextChar();
            return Token::Punctuator( start, TK::DivAssign, "/=" );

          default:
            return Token::Punctuator( start, TK::Div, "/" );
        }

      default:
        return lexKeywordOrIdentifier();
    } // end switch
  } // end for
} // end getToken

//
//  Keyword or Identifier
//
Token Lexer::lexKeywordOrIdentifier()
{
  Pos start( pos );
  if ( ! isalnum( c ) && c != '_' )
  {
    buf += c;
    nextChar();
    errorf( start, "%s %s", buf.c_str(), "illegal identifier" );
  }
  while ( isalnum( c ) || c == '_' )
  {
    buf += c;
    nextChar();
  }
  auto it = Keywords.find( buf.c_str() ) ;
  if ( it != Keywords.end() )
    return Token::Keyword( start, buf );

  return Token::Identifier( start, buf );
}

//
//  Numerical Constant
//
Token Lexer::lexNumericalConstant()
{
  Pos start( pos );
  while ( isdigit( c ) )
  {
    buf += c;
    nextChar();
  }
  return Token::Constant( start, buf );
}

Token Lexer::lexCharConstOrStringLiteral()
{
  Pos start( pos );
  Pos * illegalEscapeSequence = 0;
  buf += c;
  int terminator = c;
  bool empty = true;
  nextChar();
  for (;;)
  {
    if ( c == -1 || c == '\n' )
      goto newline;

    if ( c == terminator )
    {
      buf += c;
      nextChar();
      break;
    }

    if ( c == '\\' )
    {
      buf += c;
      nextChar();
      switch ( c )
      {
        case '\'':
        case '\"':
        case '?':
        case '\\':
        case 'a':
        case 'b':
        case 'f':
        case 'n':
        case 'r':
        case 't':
        case 'v':
        case '0':
          break;

        default:
          illegalEscapeSequence = new Pos( pos );
      }
    }

    buf += c;
    nextChar();
    empty = false;
  }

  if ( empty && terminator == '\'' )
    errorf( start, "%s - %s", buf.c_str(), "empty character constant" );

  if ( illegalEscapeSequence )
    errorf( *illegalEscapeSequence, "%s - %s", buf.c_str(),
        "illegal escape sequence" );

  if ( terminator == '\'' )
    return Token::Constant( start, buf );
  return Token::StringLiteral( start, buf );

newline:
  if ( c == '"' )
    errorf( start, "%s %s - %s", "string-literal", buf.c_str(),
        "missing terminating quote" );
  else
    errorf( start, "%s %s - %s", "constant", buf.c_str(),
        "missing terminating apostrophe" );
  return Token::StringLiteral( start, buf );
}

//}
////
////  Punctuator
////
//else
//{
//switch ( c )
//{
//// Punctuators that consist of a single character
//}
//}
//}
