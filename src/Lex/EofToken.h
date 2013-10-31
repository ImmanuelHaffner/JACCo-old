//===--- EofToken.h -------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the tokens.
//
//===----------------------------------------------------------------------===//

#ifndef C4_EOF_TOKEN
#define C4_EOF_TOKEN

#include "Token.h"

namespace C4
{
  namespace Lex
  {
    struct EofToken : Token
    {
      EofToken( Pos const &pos ) :
        Token( pos, TokenKind::END_OF_FILE, "" )
      {}

      virtual ~EofToken() {}

      friend std::ostream & operator<<( std::ostream &out,
          EofToken const &tok );

      void dump() const;
    };
  } // end namespace Lex
} // end namespace C4

#endif
