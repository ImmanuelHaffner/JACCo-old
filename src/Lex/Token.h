//===--- Token.h ----------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the tokens.
//
//===----------------------------------------------------------------------===//

#ifndef C4_TOKEN_H
#define C4_TOKEN_H

#include <iostream>
#include <map>
#include <set>
#include <string>
#include "../pos.h"
#include "../util.h"
#include "../Support/Symbol.h"
#include <unordered_map>

namespace C4
{
  namespace Lex
  {
		/// The kind of a token.
    enum class TK
    {
      IDENTIFIER,
      CONSTANT,
      STRING_LITERAL,
      END_OF_FILE,

      // Keywords
      Auto,
      Break,
      Case,
      Char,
      Const,
      Continue,
      Default,
      Do,
      Double,
      Else,
      Enum,
      Extern,
      Float,
      For,
      Goto,
      If,
      Inline,
      Int,
      Long,
      Register,
      Restrict,
      Return,
      Short,
      Signed,
      Sizeof,
      Static,
      Struct,
      Switch,
      Typedef,
      Union,
      Unsigned,
      Void,
      Volatile,
      While,
      Alignas,
      Alignof,
      Atomic,
      Bool,
      Complex,
      Generic,
      Imaginary,
      Noreturn,
      Static_assert,
      Thread_local,

      // Punctuators
      LBracket,
      RBracket,
      LPar,
      RPar,
      LBrace,
      RBrace,
      Dot,
      PtrOp,
      IncOp,
      DecOp,
      And,
      Mul,
      Plus,
      Minus,
      Neg,
      Not,
      Div,
      Mod,
      LShift,
      RShift,
      Le,
      Gr,
      LEq,
      GEq,
      Eq,
      NE,
      Xor,
      Or,
      LAnd,
      LOr,
      QMark,
      Col,
      SCol,
      Ellipsis,
      Assign,
      MulAssign,
      DivAssign,
      ModAssign,
      AddAssign,
      SubAssign,
      LShiftAssign,
      RShiftAssign,
      AndAssign,
      XorAssign,
      OrAssign,
      Comma,
      Hash,
      DHash
    };

    std::ostream & operator<<( std::ostream &out, TK tk );

    /// A token...
    struct Token
    {
      // KEYWORD
      static Token Keyword( Pos const &pos, TK tk, char const * const text )
      {
        return Token( pos, tk, text );
      }

      static Token Keyword( Pos const &pos, TK tk, std::string const &text )
      {
        return Keyword( pos, tk, text.c_str() );
      }

      static Token Keyword( Pos const &pos, TK tk, Symbol const &sym )
      {
        return Token( pos, tk, sym );
      }

      // IDENTIFIER
      static Token Identifier( Pos const &pos, char const * const text )
      {
        return Token( pos, TK::IDENTIFIER, text );
      }

      static Token Identifier( Pos const &pos, std::string const &text )
      {
        return Identifier( pos, text.c_str() );
      }

      static Token Identifier( Pos const &pos, Symbol const &sym )
      {
        return Token( pos, TK::IDENTIFIER, sym );
      }

      // CONSTANT
      static Token Constant( Pos const &pos, char const * const text )
      {
        return Token( pos, TK::CONSTANT, text );
      }

      static Token Constant( Pos const &pos, std::string const &text )
      {
        return Constant( pos, text.c_str() );
      }

      // STRING-LITERAL
      static Token StringLiteral( Pos const &pos, char const * const text )
      {
        return Token( pos, TK::STRING_LITERAL, text );
      }

      static Token StringLiteral( Pos const &pos, std::string const &text )
      {
        return StringLiteral( pos, text.c_str() );
      }

      // PUNCTUATOR
      static Token Punctuator( Pos const &pos, TK tk,
          char const * const text )
      {
        return Token( pos, tk, text );
      }

      static Token Punctuator( Pos const &pos, TK tk, std::string const &text )
      {
        return Punctuator( pos, tk, text.c_str() );
      }

      // END-OF-FILE
      static Token EndOfFile( Pos const &pos )
      {
        return Token( pos, TK::END_OF_FILE, "" );
      }


      Token( Pos const &pos, TK kind, char const * const text ) :
        pos(pos), kind(kind), sym(nonNull(text))
      {}

      Token( Pos const &pos, TK kind, std::string const &text ) :
        pos(pos), kind(kind), sym(text)
      {}

      Token( Pos const &pos, TK kind, Symbol const &sym ) :
        pos(pos), kind(kind), sym(sym)
      {}

      ~Token() {}

      friend std::ostream & operator<<( std::ostream &out, Token const &tok );
      void dump() const;

      Pos const pos;
      TK const kind;
      Symbol sym;

      static std::unordered_map< Symbol, TK > KeywordsTable;
      static void INIT_KEYWORDS_TABLE();

      private:
      inline bool isKeyword() const
      {
        return KeywordsTable.find( sym ) != KeywordsTable.end();
      }
    }; // end struct Token

    std::ostream & operator<<( std::ostream &out, Token const &tok );
  } // end namespace Lex
} // end namespace C4

#endif
