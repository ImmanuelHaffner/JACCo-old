//===--- KeywordToken.h ---------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the tokens.
//
//===----------------------------------------------------------------------===//

#ifndef C4_KEYWORD_TOKEN_H
#define C4_KEYWORD_TOKEN_H

#include <iostream>
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
      WHILE,
      _ALIGNAS,
      _ALIGNOF,
      _ATOMIC,
      _BOOL,
      _COMPLEX,
      _GENERIC,
      _IMAGINARY,
      _NORETURN,
      _STATIC_ASSERT,
      _THREAD_LOCAL
    };

    static std::map<std::string, KeywordKind> Keywords =
    {
      { "auto",           KeywordKind::AUTO },
      { "break",          KeywordKind::BREAK },
      { "case",           KeywordKind::CASE },
      { "char",           KeywordKind::CHAR },
      { "const",          KeywordKind::CONST },
      { "continue",       KeywordKind::CONTINUE },
      { "default",        KeywordKind::DEFAULT },
      { "do",             KeywordKind::DO },
      { "double",         KeywordKind::DOUBLE },
      { "else",           KeywordKind::ELSE },
      { "enum",           KeywordKind::ENUM },
      { "extern",         KeywordKind::EXTERN },
      { "float",          KeywordKind::FLOAT },
      { "for",            KeywordKind::FOR },
      { "goto",           KeywordKind::GOTO },
      { "if",             KeywordKind::IF },
      { "inline",         KeywordKind::INLINE },
      { "int",            KeywordKind::INT },
      { "long",           KeywordKind::LONG },
      { "register",       KeywordKind::REGISTER },
      { "restrict",       KeywordKind::RESTRICT },
      { "return",         KeywordKind::RETURN },
      { "short",          KeywordKind::SHORT },
      { "signed",         KeywordKind::SIGNED },
      { "sizeof",         KeywordKind::SIZEOF },
      { "static",         KeywordKind::STATIC },
      { "struct",         KeywordKind::STRUCT },
      { "switch",         KeywordKind::SWITCH },
      { "typedef",        KeywordKind::TYPEDEF },
      { "union",          KeywordKind::UNION },
      { "unsigned",       KeywordKind::UNSIGNED },
      { "void",           KeywordKind::VOID },
      { "volatile",       KeywordKind::VOLATILE },
      { "while",          KeywordKind::WHILE },
      { "_Alignas",       KeywordKind::_ALIGNAS },
      { "_Alignof",       KeywordKind::_ALIGNOF },
      { "_Atomic",        KeywordKind::_ATOMIC },
      { "_Bool",          KeywordKind::_BOOL },
      { "_Complex",       KeywordKind::_COMPLEX },
      { "_Generic",       KeywordKind::_GENERIC },
      { "_Imaginary",     KeywordKind::_IMAGINARY },
      { "_Noreturn",      KeywordKind::_NORETURN },
      { "_Static_assert", KeywordKind::_STATIC_ASSERT },
      { "_Thread_local",  KeywordKind::_THREAD_LOCAL }
    };

    struct KeywordToken : Token
    {
      KeywordToken( Pos const &pos, KeywordKind keyword, char const * const text ) :
        Token( pos, TokenKind::KEYWORD, text ), keyword(keyword)
      {}

      KeywordToken( Pos const &pos, KeywordKind keyword, std::string const &text ) :
        Token( pos, TokenKind::KEYWORD, text ), keyword(keyword)
      {}

      virtual ~KeywordToken() {}

			Token & clone() const;
      friend std::ostream & operator<<( std::ostream &out,
          KeywordToken const &tok );
      void dump() const;

      KeywordKind const keyword;
    };
  } // end namespace Lex
} // end namespace C4

#endif
