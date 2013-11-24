//===--- Lexer.h ----------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the Lexer interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_LEXER_H
#define C4_LEXER_H

#include <string>
#include <fstream>
#include "Token.h"
#include "../pos.h"
#include "../Support/File.h"
#include "../Support/RegularFile.h"
#include "../Support/MemMapFile.h"
#include "../Support/StrBuf.h"

namespace C4
{
  /// \brief Defines the interface for the lexer.
  ///
  /// The lexer reads in a stream of characters and generates a stream of
  /// tokens.
  namespace Lex
  {
    /// \brief The lexer.
    ///
    ///
    class Lexer
    {
      public:
        Lexer();
        explicit Lexer( char const * const fileName );
        explicit Lexer( std::string const &fileName );
        ~Lexer();

        Pos getPos() const;
        Token getToken();

        std::string const fileName;

      private:
        int c = ' ';
        StrBuf buf;
        Pos pos;
        File &file;

        Token lexKeywordOrIdentifier();
        Token lexNumericalConstant();
        Token lexCharConstOrStringLiteral();

        inline void nextChar()
        {
          c = updatePos( file.get() );
          while ( c == '\\' && file.peek() == '\n' )
          {
            updatePos( file.get() );
            c = updatePos( file.get() );
          }
        }

        inline int updatePos( int c )
        {
          if ( c == EOF )
            return c;

          if ( c == '\n' )
          {
            ++pos.line;
            pos.column = 0;
          }
          else
            ++pos.column;

          return c;
        }
    };
  } // end namespace Lex
} // end namespace C4

#endif
