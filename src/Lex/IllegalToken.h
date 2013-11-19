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
      HEX_CONSTANT,
      ESCAPE_SEQUENCE
    };

    static std::map< IllegalTokenKind, std::string > IllegalTokenKindNames =
    {
      { IllegalTokenKind::UNKNOWN,
        "unknown token" },
      { IllegalTokenKind::IDENTIFIER,
        "illegal identifier" },
      { IllegalTokenKind::EMPTY_CHARACTER_CONSTANT,
        "empty character constant" },
      { IllegalTokenKind::CONSTANT_MULTIPLE_CHARACTERS,
        "character constant with multiple characters" },
      { IllegalTokenKind::MISSING_APOSTROPHE,
        "missing terminating apostrophe" },
      { IllegalTokenKind::MISSING_QUOTE,
        "missing terminating quote" },
      { IllegalTokenKind::MISSING_COMMENT_TERMINATOR,
        "unterminated comment block" },
      { IllegalTokenKind::ESCAPE_SEQUENCE,
        "illegal escape sequence" },
      { IllegalTokenKind::HEX_CONSTANT,
        "illegal hexadecimal constant" }
    };

    std::ostream & operator<<( std::ostream &out, IllegalTokenKind iKind );

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

    std::ostream & operator<<( std::ostream &out, IllegalToken const &tok );
  } // end namespace Lex
} // end namespace C4

#endif
