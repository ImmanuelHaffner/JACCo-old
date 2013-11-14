//===--- IllegalToken.h ---------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the tokens.
//
//===----------------------------------------------------------------------===//

#ifndef C4_ILLEGAL_TOKEN_H
#define C4_ILLEGAL_TOKEN_H

#include "Token.h"

namespace C4
{
  namespace Lex
  {
    enum class IllegalTokenKind
    {
      UNKNOWN,
      IDENTIFIER,
			EMPTY_CHARACTER_CONSTANT,
      CONSTANT_MULTIPLE_CHARACTERS,
      MISSING_APOSTROPHE,
      MISSING_QUOTE,
      MISSING_COMMENT_TERMINATOR,
      ESCAPE_SEQUENCE
    };

    struct IllegalToken : Token
    {
      IllegalToken( Pos const &pos, IllegalTokenKind iKind,
          char const * const text ) :
        Token( pos, TokenKind::ILLEGAL, text ), iKind(iKind)
      {}

      IllegalToken( Pos const &pos, IllegalTokenKind iKind,
          std::string const &text ) :
        Token( pos, TokenKind::ILLEGAL, text ), iKind(iKind)
      {}

      virtual ~IllegalToken() {}

			Token & clone() const;
      friend std::ostream & operator<<( std::ostream &out,
          IllegalToken const &tok );
      void dump( std::ostream &out = std::cout ) const;

      IllegalTokenKind const iKind;
    };
  } // end namespace Lex
} // end namespace C4

#endif
