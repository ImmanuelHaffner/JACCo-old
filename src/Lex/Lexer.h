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
#include "../Support/SourceBuffer.h"
#include "../Support/SourceLocation.h"

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
				Lexer( SourceBuffer &buf );
				~Lexer();

				/// Reads and returns the next token on the input stream.
				///
				/// \return the next token from the input stream
				Token * getToken();

			private:
				inline unsigned getTokenID()
				{
					return ++tokenCount;
				}

				/// Steps one character forward in the buffer and updates 'it' and
				/// 'pos'.
				/// Immediately skips escaped newlines
        ///
        /// \return false, iff the end of the buffer is reached, true otherwise
				bool step( char &lastChar);

        /// This method skips until the first non-whitespace character, that
        /// is not part of a comment
        ///
        /// \return false, iff the end of the buffer is reached, true otherwise
        bool skip( char &lastChar );

				/// This methods skips the '\' follwed by a newline
        ///
        /// \return false, iff the end of the buffer is reached, true otherwise
				bool skipEscapedNewline( char &lastChar );

				unsigned tokenCount;
				SourceBuffer &buf;
				Pos pos;
				std::vector<char>::const_iterator it;
		};
	} // end namespace Lex
} // end namespace C4

#endif
