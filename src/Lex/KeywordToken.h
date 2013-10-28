//===--- KeywordToken.h ---------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the tokens.
//
//===----------------------------------------------------------------------===//

#ifndef C4_KEYWORD_TOKEN_H
#define C4_KEYWORD_TOKEN_H

#include "Token.h"

namespace C4
{
  namespace Lex
  {

    //===----------------------------------------------------------------------
    //
    //  Definition of the keywords
    //
    //===----------------------------------------------------------------------
    enum class KeywordKind
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

    static std::map<std::string, KeywordKind> Keywords =
    {
      { "auto",         KeywordKind::AUTO },
      { "break",        KeywordKind::BREAK },
      { "case",         KeywordKind::CASE },
      { "char",         KeywordKind::CHAR },
      { "const",        KeywordKind::CONST },
      { "continue",     KeywordKind::CONTINUE },
      { "default",      KeywordKind::DEFAULT },
      { "do",           KeywordKind::DO },
      { "double",       KeywordKind::DOUBLE },
      { "else",         KeywordKind::ELSE },
      { "enum",         KeywordKind::ENUM },
      { "extern",       KeywordKind::EXTERN },
      { "float",        KeywordKind::FLOAT },
      { "for",          KeywordKind::FOR },
      { "goto",         KeywordKind::GOTO },
      { "if",           KeywordKind::IF },
      { "inline",       KeywordKind::INLINE },
      { "int",          KeywordKind::INT },
      { "long",         KeywordKind::LONG },
      { "register",     KeywordKind::REGISTER },
      { "restrict",     KeywordKind::RESTRICT },
      { "return",       KeywordKind::RETURN },
      { "short",        KeywordKind::SHORT },
      { "signed",       KeywordKind::SIGNED },
      { "sizeof",       KeywordKind::SIZEOF },
      { "static",       KeywordKind::STATIC },
      { "struct",       KeywordKind::STRUCT },
      { "switch",       KeywordKind::SWITCH },
      { "typedef",      KeywordKind::TYPEDEF },
      { "union",        KeywordKind::UNION },
      { "unsigned",     KeywordKind::UNSIGNED },
      { "void",         KeywordKind::VOID },
      { "volatile",     KeywordKind::VOLATILE },
      { "while",        KeywordKind::WHILE },
    };

    struct KeywordToken : Token
    {
      KeywordToken( Pos const &pos, KeywordKind keyword, char const * const text ) :
        Token( pos, TokenKind::KEYWORD, text ), keyword(keyword)
      {}

      KeywordToken( Pos const &pos, KeywordKind keyword, std::string const &text ) :
        Token( pos, TokenKind::KEYWORD, text ), keyword(keyword)
      {}

      void dump() const;

      KeywordKind const keyword;
    };

  } // end namespace Lex
} // end namespace C4

#endif
