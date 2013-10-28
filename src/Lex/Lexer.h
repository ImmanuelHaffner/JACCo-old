//===--- Lexer.h ----------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the Lexer interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_LEXER_H
#define C4_LEXER_H

#include "Token.h"
#include "../pos.h"
#include "../util.h"

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
        Lexer( char const * const fileName, FILE * file );
        Lexer( std::string const &fileName, FILE * file );

        ~Lexer();

        /// Reads and returns the next token on the input stream.
        ///
        /// \return the next token from the input stream
        Token * getToken();

        Pos getPos() const;

        /// Steps one character forward in the file and updates 'pos'.
        /// Immediately skips escaped newlines.
        ///
        /// \return false, iff the end of the buffer is reached, true otherwise
        bool step( int &current);

        /// This method skips until the first non-whitespace character, that
        /// is not part of a comment.
        ///
        /// \return false, iff the end of the buffer is reached, true otherwise
        bool skip( int &current );

        ///
        Token * readKeywordOrIdentifier( int &current );

        std::string const fileName;

      private:
        FILE * file;
        Pos pos;
    };
  } // end namespace Lex
} // end namespace C4

#endif
