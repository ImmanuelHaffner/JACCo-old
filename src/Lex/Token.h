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

namespace C4
{
  namespace Lex
  {

		/// The kind of a token.
    enum class TokenKind
    {
      KEYWORD,
      IDENTIFIER,
      CONSTANT,
      STRING_LITERAL,
      PUNCTUATOR,
      ILLEGAL,
      END_OF_FILE
    };

    static std::map< TokenKind, std::string > TokenKindNames =
    {
      { TokenKind::KEYWORD,        "keyword" },
      { TokenKind::IDENTIFIER,     "identifier" },
      { TokenKind::CONSTANT,       "constant" },
      { TokenKind::STRING_LITERAL, "string-literal" },
      { TokenKind::PUNCTUATOR,     "punctuator" },
      { TokenKind::END_OF_FILE,    "end-of-file" },
      { TokenKind::ILLEGAL,        "illegal" }
    };


    /// A token...
    struct Token
    {
      // KEYWORD
      static Token & Keyword( Pos const &pos, char const * const text )
      {
        return *( new Token( pos, TokenKind::KEYWORD, text ) );
      }

      static Token & Keyword( Pos const &pos, std::string const &text )
      {
        return Keyword( pos, text.c_str() );
      }

      // IDENTIFIER
      static Token & Identifier( Pos const &pos, char const * const text )
      {
        return *( new Token( pos, TokenKind::IDENTIFIER, text ) );
      }

      static Token & Identifier( Pos const &pos, std::string const &text )
      {
        return Identifier( pos, text.c_str() );
      }

      // CONSTANT
      static Token & Constant( Pos const &pos, char const * const text )
      {
        return *( new Token( pos, TokenKind::CONSTANT, text ) );
      }

      static Token & Constant( Pos const &pos, std::string const &text )
      {
        return Constant( pos, text.c_str() );
      }

      // STRING-LITERAL
      static Token & StringLiteral( Pos const &pos, char const * const text )
      {
        return *( new Token( pos, TokenKind::STRING_LITERAL, text ) );
      }

      static Token & StringLiteral( Pos const &pos, std::string const &text )
      {
        return StringLiteral( pos, text.c_str() );
      }

      // PUNCTUATOR
      static Token & Punctuator( Pos const &pos, char const * const text )
      {
        return *( new Token( pos, TokenKind::PUNCTUATOR, text ) );
      }

      static Token & Punctuator( Pos const &pos, std::string const &text )
      {
        return Punctuator( pos, text.c_str() );
      }

      // END-OF-FILE
      static Token & EndOfFile( Pos const &pos )
      {
        return *( new Token( pos, TokenKind::END_OF_FILE, "" ) );
      }


      Token( Pos const &pos, TokenKind kind, char const * const text ) :
        pos(pos), kind(kind), text(nonNull(text))
      {}

      Token( Pos const &pos, TokenKind kind, std::string const &text ) :
        pos(pos), kind(kind), text(text)
      {}

      virtual ~Token() {}

      virtual Token & clone() const;
      friend std::ostream & operator<<( std::ostream &out, Token const &tok );
      virtual void dump() const;

      Pos const pos;
      TokenKind const kind;
      std::string const text;
    };

    static std::set<std::string> Keywords =
    {
      "auto",           
      "break",          
      "case",           
      "char",           
      "const",          
      "continue",       
      "default",        
      "do",             
      "double",         
      "else",           
      "enum",           
      "extern",         
      "float",          
      "for",            
      "goto",           
      "if",             
      "inline",         
      "int",            
      "long",           
      "register",       
      "restrict",       
      "return",         
      "short",          
      "signed",         
      "sizeof",         
      "static",         
      "struct",         
      "switch",         
      "typedef",        
      "union",          
      "unsigned",       
      "void",           
      "volatile",       
      "while",          
      "_Alignas",       
      "_Alignof",       
      "_Atomic",        
      "_Bool",          
      "_Complex",       
      "_Generic",       
      "_Imaginary",     
      "_Noreturn",      
      "_Static_assert", 
      "_Thread_local",  
    };

		static std::set< std::string > Punctuators =
		{
      "[",
      "]",
      "(",
      ")",
      "{",
      "}",
      ".",
      "->",
      "++",
      "--",
      "&",
      "*",
      "+",
      "-",
      "~",
      "!",
      "/",
      "%",
      "<<",
      ">>",
      "<",
      ">",
      "<=",
      ">=",
      "==",
      "!=",
      "^",
      "|",
      "&&",
      "||",
      "?",
      ":",
      ";",
      "...",
      "=",
      "*=",
      "/=",
      "%=",
      "+=",
      "-=",
      "<<=",
      ">>=",
      "&=",
      "^=",
      "|=",
      "," 
      "#",
      "##"
		};
  } // end namespace Lex
} // end namespace C4

#endif
