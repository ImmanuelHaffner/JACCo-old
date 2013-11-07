//===--- Token.h ----------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the tokens.
//
//===----------------------------------------------------------------------===//

#ifndef C4_TOKEN_H
#define C4_TOKEN_H

#include <iostream>
#include <map>
#include <string>
#include "../pos.h"
#include "../util.h"

namespace C4
{
  namespace Lex
  {

		/// The kind of a token.
    enum class TokenKind
    {
      KEYWORD,
      IDENTIFIER,
      CONSTANT,
      STRING_LITERAL,
      PUNCTUATOR,
      ILLEGAL,
      END_OF_FILE
    };


    /// A token...
    struct Token
    {
      Token( Pos const &pos, TokenKind kind, char const * const text ) :
        pos(pos), kind(kind), text(nonNull(text))
      {}

      Token( Pos const &pos, TokenKind kind, std::string const &text ) :
        pos(pos), kind(kind), text(text)
      {}

      virtual ~Token() {}

			virtual Token & clone() const;
      friend std::ostream & operator<<( std::ostream &out, Token const &tok );
      virtual void dump() const;

      Pos const pos;
      TokenKind const kind;
      std::string const text;
    };
  } // end namespace Lex
} // end namespace C4

#endif
