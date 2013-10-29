//===--- Lexer.h ----------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the Lexer interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_LEXER_H
#define C4_LEXER_H

#include <fstream>
#include "Token.h"
#include "../pos.h"

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
        Lexer( char const * const fileName );
        Lexer( std::string const &fileName );

        ~Lexer();

        /// Reads and returns the next token on the input stream.
        ///
        /// \return the next token from the input stream
        Token & getToken();

        Pos getPos() const;

        char current() const;

        /// \return a KEYWORD or IDENTIFIER
        Token & readKeywordOrIdentifier();

        /// \return a Numerical CONSTANT, or an ILLEGAL Token
        Token & readNumericalConstant();

        /// \return a Character CONSTANT, or an ILLEGAL Token
        Token & readCharacterConstant();

        std::string const fileName;

        /// Skips until the next non-whitespace character, that is not part of
        /// a comment.
        /// Reads at least one character.
        void skip();

        void updatePos( int c );

      private:
        std::istream &file;
        Pos pos;
    };
  } // end namespace Lex
} // end namespace C4

#endif
