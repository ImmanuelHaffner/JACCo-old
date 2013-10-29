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

        /// Reads a keyword or an identifier.
        /// Stops at the first character not part of the keyword or the
        /// identifier, such that file.peek() would return that character.
        /// Reads at least one character.
        ///
        /// \return a KEYWORD or IDENTIFIER
        Token & readKeywordOrIdentifier();

        /// Reads a numerical constant.
        /// Stops at the first character not part of the numerical constant,
        /// such that file.peek() would return that character.
        /// Reads at least one character.
        ///
        /// \return a Numerical CONSTANT, or an ILLEGAL Token
        Token & readNumericalConstant();

        /// Reads a character constant or a string literal.
        /// Stops at the first character not part of the character constant
        /// or the string literal, such that file.peek() would return that
        /// character.
        /// Reads at least one character.
        ///
        /// \return a Character CONSTANT, a STRING LITERAL, or an ILLEGAL Token
        Token & readCharacterConstantOrStringLiteral();

        std::string const fileName;

        /// Skips until the next non-whitespace character, that is not part of
        /// a comment.
        /// Stops at the first non-whitespace character not part of a comment,
        /// such that file.peek() would return that character.
        void skip();

        /// Reads exactly one character and updates the position.
        void step();

        void updatePos( int c );

      private:
        std::istream &file;
        Pos pos;
    };
  } // end namespace Lex
} // end namespace C4

#endif
