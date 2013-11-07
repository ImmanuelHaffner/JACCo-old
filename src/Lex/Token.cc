//===--- Token.cc ---------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the tokens.
//
//===----------------------------------------------------------------------===//

#include "Token.h"

#include <iostream>
#include "../Support/Diagnostic.h"
#include "KeywordToken.h"
#include "IdentifierToken.h"
#include "ConstantToken.h"
#include "StringLiteralToken.h"
#include "PunctuatorToken.h"
#include "IllegalToken.h"
#include "EofToken.h"

using namespace C4;
using namespace Lex;

Token & Token::clone() const
{
	return *( new Token( *this ) );
}

std::ostream & Lex::operator<<( std::ostream &out, Token const &tok )
{
  switch ( tok.kind )
  {
    case TokenKind::KEYWORD:
        out << static_cast< KeywordToken const & >( tok );
        break;
    case TokenKind::IDENTIFIER:
        out << static_cast< IdentifierToken const & >( tok );
        break;
    case TokenKind::CONSTANT:
        out << static_cast< ConstantToken const & >( tok );
        break;
    case TokenKind::STRING_LITERAL:
        out << static_cast< StringLiteralToken const & >( tok );
        break;
    case TokenKind::PUNCTUATOR:
        out << static_cast< PunctuatorToken const & >( tok );
        break;
    case TokenKind::ILLEGAL:
        out << static_cast< IllegalToken const & >( tok );
        break;
    case TokenKind::END_OF_FILE:
        out << static_cast< EofToken const & >( tok );
        break;

    default:
        out << "unknwon token kind";
  }

  return out;
}

void Token::dump() const
{
  std::cout << *this;
}
