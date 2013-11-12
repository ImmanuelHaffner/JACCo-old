//===--- IdentifierToken.h ------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the tokens.
//
//===----------------------------------------------------------------------===//

#ifndef C4_IDENTIFIER_TOKEN_H
#define C4_IDENTIFIER_TOKEN_H

#include <iostream>
#include "Token.h"

namespace C4
{
  namespace Lex
  {
    struct IdentifierToken : Token
    {
      IdentifierToken( Pos const &pos, char const * const text ) :
        Token( pos, TokenKind::IDENTIFIER, text )
      {}

      IdentifierToken( Pos const &pos, std::string const &text ) :
        Token( pos, TokenKind::IDENTIFIER, text )
      {}

      virtual ~IdentifierToken() {}

			Token & clone() const;
    };
  } // end namespace Lex
} // end namespace C4

#endif
