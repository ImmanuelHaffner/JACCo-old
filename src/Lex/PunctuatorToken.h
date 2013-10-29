//===--- Punctuator.h -----------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the tokens.
//
//===----------------------------------------------------------------------===//

#ifndef C4_PUNCTUATOR_TOKEN_H
#define C4_PUNCTUATOR_TOKEN_H

#include "Token.h"

namespace C4
{
  namespace Lex
  {
    //===----------------------------------------------------------------------
    //
    //  Definition of the punctuators
    //
    //===----------------------------------------------------------------------
		enum class PunctuatorKind
		{
			LBRACKET,
			RBRACKET,
			LPAR,
			RPAR,
			LBRACE,
			RBRACE,
			DOT,
			LARROW,
			INC,
			DEC,
			AND,
			MUL,
			PLUS,
			MINUS,
			NEG,
			NOT,
			DIV,
			PERC,
			LSHIFT,
			RSHIFT,
			LE,
			GR,
			LEQ,
			GEQ,
			EQ,
			NEQ,
			XOR,
			OR,
			LAND,
			LOR,
			CONDITIONAL,
			COL,
			SCOL,
			LDOTS,
			ASSIGN,
			MULASSIGN,
			DIVASSIGN,
			MODASSIGN,
			ADDASSIGN,
			SUBASSIGN,
			LSHIFTASSIGN,
			RSHIFTASSIGN,
			ANDASSIGN,
			XORASSIGN,
			ORASSIGN,
			COMMA,
			HASH,
			DHASH
		};

    struct PunctuatorToken : Token
    {
      PunctuatorToken( Pos const &pos, PunctuatorKind punctuator, char const * const text ) :
        Token( pos, TokenKind::PUNCTUATOR, text ), punctuator(punctuator)
      {}

      PunctuatorToken( Pos const &pos, PunctuatorKind punctuator, std::string const &text ) :
        Token( pos, TokenKind::PUNCTUATOR, text ), punctuator(punctuator)
      {}

      virtual ~PunctuatorToken() {}

      void dump() const;

      PunctuatorKind const punctuator;
    };

  } // end namespace Lex
} // end namespace C4

#endif
