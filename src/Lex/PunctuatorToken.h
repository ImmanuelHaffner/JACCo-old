//===--- Punctuator.h -----------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the tokens.
//
//===----------------------------------------------------------------------===//

#ifndef C4_PUNCTUATOR_TOKEN_H
#define C4_PUNCTUATOR_TOKEN_H

#include <iostream>
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
			LBRACKET,     // [
			RBRACKET,     // ]
			LPAR,         // (
			RPAR,         // )
			LBRACE,       // {
			RBRACE,       // }
			DOT,          // .
			ARROW,        // ->
			INC,          // ++
			DEC,          // --
			AND,          // &
			MUL,          // *
			PLUS,         // +
			MINUS,        // -
			NEG,          // ~
			NOT,          // !
			DIV,          // /
			MOD,          // %
			LSHIFT,       // <<
			RSHIFT,       // >>
			LE,           // <
			GR,           // >
			LEQ,          // <=
			GEQ,          // >=
			EQ,           // ==
			NE,           // !=
			XOR,          // ^
			OR,           // |
			LAND,         // &&
			LOR,          // ||
			QMARK,        // ?
			COLON,        // :
			SEMICOLON,    // ;
			ELLIPSIS,     // ...
			ASSIGN,       // =
			MULASSIGN,    // *=
			DIVASSIGN,    // /=
			MODASSIGN,    // %=
			ADDASSIGN,    // +=
			SUBASSIGN,    // -=
			LSHIFTASSIGN, // <<=
			RSHIFTASSIGN, // >>=
			ANDASSIGN,    // &=
			XORASSIGN,    // ^=
			ORASSIGN,     // |=
			COMMA,        // ,
			HASH,         // #
			DHASH         // ##
		};

		static std::map< PunctuatorKind, std::string > PunctuatorKindNames =
		{
      { PunctuatorKind::LBRACKET,       "[" },
      { PunctuatorKind::RBRACKET,       "]" },
      { PunctuatorKind::LPAR,           "(" },
      { PunctuatorKind::RPAR,           ")" },
      { PunctuatorKind::LBRACE,         "{" },
      { PunctuatorKind::RBRACE,         "}" },
      { PunctuatorKind::DOT,            "." },
      { PunctuatorKind::ARROW,          "->" },
      { PunctuatorKind::INC,            "++" },
      { PunctuatorKind::DEC,            "--" },
      { PunctuatorKind::AND,            "&" },
      { PunctuatorKind::MUL,            "*" },
      { PunctuatorKind::PLUS,           "+" },
      { PunctuatorKind::MINUS,          "-" },
      { PunctuatorKind::NEG,            "~" },
      { PunctuatorKind::NOT,            "!" },
      { PunctuatorKind::DIV,            "/" },
      { PunctuatorKind::MOD,            "%" },
      { PunctuatorKind::LSHIFT,         "<<" },
      { PunctuatorKind::RSHIFT,         ">>" },
      { PunctuatorKind::LE,             "<" },
      { PunctuatorKind::GR,             ">" },
      { PunctuatorKind::LEQ,            "<=" },
      { PunctuatorKind::GEQ,            ">=" },
      { PunctuatorKind::EQ,             "==" },
      { PunctuatorKind::NE,             "!=" },
      { PunctuatorKind::XOR,            "^" },
      { PunctuatorKind::OR,             "|" },
      { PunctuatorKind::LAND,           "&&" },
      { PunctuatorKind::LOR,            "||" },
      { PunctuatorKind::QMARK,          "?" },
      { PunctuatorKind::COLON,          ":" },
      { PunctuatorKind::SEMICOLON,      ";" },
      { PunctuatorKind::ELLIPSIS,       "..." },
      { PunctuatorKind::ASSIGN,         "=" },
      { PunctuatorKind::MULASSIGN,      "*=" },
      { PunctuatorKind::DIVASSIGN,      "/=" },
      { PunctuatorKind::MODASSIGN,      "%=" },
      { PunctuatorKind::ADDASSIGN,      "+=" },
      { PunctuatorKind::SUBASSIGN,      "-=" },
      { PunctuatorKind::LSHIFTASSIGN,   "<<=" },
      { PunctuatorKind::RSHIFTASSIGN,   ">>=" },
      { PunctuatorKind::ANDASSIGN,      "&=" },
      { PunctuatorKind::XORASSIGN,      "^=" },
      { PunctuatorKind::ORASSIGN,       "|=" },
      { PunctuatorKind::COMMA,          "," },
      { PunctuatorKind::HASH,           "#" },
      { PunctuatorKind::DHASH,          "##" }
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

			Token & clone() const;

      PunctuatorKind const punctuator;
    };
  } // end namespace Lex
} // end namespace C4

#endif
