//===--- ConstantToken.h --------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the tokens.
//
//===----------------------------------------------------------------------===//

#ifndef C4_CONSTANT_TOKEN_H
#define C4_CONSTANT_TOKEN_H

#include <iostream>
#include "Token.h"

namespace C4
{
  namespace Lex
  {
    struct ConstantToken : Token
    {
      ConstantToken( Pos const &pos, char const * const text ) :
        Token( pos, TokenKind::CONSTANT, text )
      {}

      ConstantToken( Pos const &pos, std::string const &text ) :
        Token( pos, TokenKind::CONSTANT, text )
      {}

      virtual ~ConstantToken() {}

      friend std::ostream & operator<<( std::ostream &out,
          ConstantToken const &tok );

      void dump() const;
    };
  } // end namespace Lex
} // end namespace C4

#endif
