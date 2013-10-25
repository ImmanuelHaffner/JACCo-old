//===--- Lexer.h ----------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the Lexer interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_LEXER_H
#define C4_LEXER_H

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
		/// The kind of a token.
		enum class TokenKind
		{
			Keyword,
			Identifier,
			Constant,
			StringLiteral,
			Punctuator
		};

		/// A token...
		///
		/// TODO
		struct Token
		{
			Token( unsigned id, char const * text, TokenKind kind,
					SourceLocation const &loc ) :
				id(id), text(nonNull(text)), kind(kind), loc(loc)
			{}

			unsigned const id;
			char const * const text;
			TokenKind const kind;
			SourceLocation const &loc;
		};

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
				SourceBuffer &buf;
				Pos pos;
				std::vector<char>::const_iterator it;
		};
	} // end namespace Lex
} // end namespace C4

#endif
