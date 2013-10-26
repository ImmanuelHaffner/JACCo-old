//===--- Token.h ----------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the tokens.
//
//===----------------------------------------------------------------------===//

#ifndef C4_TOKEN_H
#define C4_TOKEN_H

#include "../Support/SourceLocation.h"
#include "../pos.h"
#include "../util.h"
#include <map>
#include <string>

namespace C4{
  namespace Lex{

		/// The kind of a token.
    enum class TokenKind
    {
      Keyword,
      Identifier,
      Constant,
      StringLiteral,
      Punctuator,
      Illegal
    };


    //===----------------------------------------------------------------------
    //
    //  Definition of the keywords
    //
    //===----------------------------------------------------------------------
    enum class Keyword
    {
			AUTO,
			BREAK,
			CASE,
			CHAR,
			CONST,
			CONTINUE,
			DEFAULT,
			DO,
			DOUBLE,
			ELSE,
			ENUM,
			EXTERN,
			FLOAT,
			FOR,
			GOTO,
			IF,
			INLINE,
			INT,
			LONG,
			REGISTER,
			RESTRICT,
			RETURN,
			SHORT,
			SIGNED,
			SIZEOF,
			STATIC,
			STRUCT,
			SWITCH,
			TYPEDEF,
			UNION,
			UNSIGNED,
			VOID,
			VOLATILE,
			WHILE
    };

    static std::map<std::string, Keyword> Keywords =
    {
      { "auto",         Keyword::AUTO },
      { "break",        Keyword::BREAK },
      { "case",         Keyword::CASE },
      { "char",         Keyword::CHAR },
      { "const",        Keyword::CONST },
      { "continue",     Keyword::CONTINUE },
      { "default",      Keyword::DEFAULT },
      { "do",           Keyword::DO },
      { "double",       Keyword::DOUBLE },
      { "else",         Keyword::ELSE },
      { "enum",         Keyword::ENUM },
      { "extern",       Keyword::EXTERN },
      { "float",        Keyword::FLOAT },
      { "for",          Keyword::FOR },
      { "goto",         Keyword::GOTO },
      { "if",           Keyword::IF },
      { "inline",       Keyword::INLINE },
      { "int",          Keyword::INT },
      { "long",         Keyword::LONG },
      { "register",     Keyword::REGISTER },
      { "restrict",     Keyword::RESTRICT },
      { "return",       Keyword::RETURN },
      { "short",        Keyword::SHORT },
      { "signed",       Keyword::SIGNED },
      { "sizeof",       Keyword::SIZEOF },
      { "static",       Keyword::STATIC },
      { "struct",       Keyword::STRUCT },
      { "switch",       Keyword::SWITCH },
      { "typedef",      Keyword::TYPEDEF },
      { "union",        Keyword::UNION },
      { "unsigned",     Keyword::UNSIGNED },
      { "void",         Keyword::VOID },
      { "volatile",     Keyword::VOLATILE },
      { "while",        Keyword::WHILE },
    };

    //===----------------------------------------------------------------------
    //
    //  Definition of the punctuators
    //
    //===----------------------------------------------------------------------
		enum class Punctuator
		{
			Punctuator_LBracket,
			Punctuator_RBracket,
			Punctuator_LPar,
			Punctuator_RPar,
			Punctuator_LBrace,
			Punctuator_RBrace,
			Punctuator_Dot,
			Punctuator_LArrow,
			Punctuator_Inc,
			Punctuator_Dec,
			Punctuator_And,
			Punctuator_Mul,
			Punctuator_Plus,
			Punctuator_Minus,
			Punctuator_Neg,
			Punctuator_Not,
			Punctuator_Div,
			Punctuator_Perc,
			Punctuator_LShift,
			Punctuator_RShift,
			Punctuator_LE,
			Punctuator_GR,
			Punctuator_LEq,
			Punctuator_GEq,
			Punctuator_Eq,
			Punctuator_NEq,
			Punctuator_XOr,
			Punctuator_Or,
			Punctuator_LAnd,
			Punctuator_LOr,
			Punctuator_Conditional,
			Punctuator_Col,
			Punctuator_SCol,
			Punctuator_LDots,
			Punctuator_Assign,
			Punctuator_MulAssign,
			Punctuator_DivAssign,
			Punctuator_ModAssign,
			Punctuator_AddAssign,
			Punctuator_SubAssign,
			Punctuator_LShiftAssign,
			Punctuator_RShiftAssign,
			Punctuator_AndAssign,
			Punctuator_XOrAssign,
			Punctuator_OrAssign,
			Punctuator_Comma,
			Punctuator_Hash,
			Punctuator_DHash
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

      void dump() const;

      unsigned const id;
      char const * const text;
      TokenKind const kind;
      SourceLocation const &loc;
    };

  } // end namespace Lex
} // end namespace C4

#endif
