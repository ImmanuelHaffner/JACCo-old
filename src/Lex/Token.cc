//===--- Token.cc ---------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the tokens.
//
//===----------------------------------------------------------------------===//

#include "Token.h"

#include <iostream>

using namespace C4;
using namespace Lex;

std::unordered_set< Symbol > Token::KeywordsTable;

void Token::INIT_KEYWORDS_TABLE()
{
  Token::KeywordsTable.insert( Symbol( "auto" ) );
  Token::KeywordsTable.insert( Symbol( "break" ) );
  Token::KeywordsTable.insert( Symbol( "case" ) );
  Token::KeywordsTable.insert( Symbol( "char" ) );
  Token::KeywordsTable.insert( Symbol( "const" ) );
  Token::KeywordsTable.insert( Symbol( "continue" ) );
  Token::KeywordsTable.insert( Symbol( "default" ) );
  Token::KeywordsTable.insert( Symbol( "do" ) );
  Token::KeywordsTable.insert( Symbol( "double" ) );
  Token::KeywordsTable.insert( Symbol( "else" ) );
  Token::KeywordsTable.insert( Symbol( "enum" ) );
  Token::KeywordsTable.insert( Symbol( "extern" ) );
  Token::KeywordsTable.insert( Symbol( "float" ) );
  Token::KeywordsTable.insert( Symbol( "for" ) );
  Token::KeywordsTable.insert( Symbol( "goto" ) );
  Token::KeywordsTable.insert( Symbol( "if" ) );
  Token::KeywordsTable.insert( Symbol( "inline" ) );
  Token::KeywordsTable.insert( Symbol( "int" ) );
  Token::KeywordsTable.insert( Symbol( "long" ) );
  Token::KeywordsTable.insert( Symbol( "register" ) );
  Token::KeywordsTable.insert( Symbol( "restrict" ) );
  Token::KeywordsTable.insert( Symbol( "return" ) );
  Token::KeywordsTable.insert( Symbol( "short" ) );
  Token::KeywordsTable.insert( Symbol( "signed" ) );
  Token::KeywordsTable.insert( Symbol( "sizeof" ) );
  Token::KeywordsTable.insert( Symbol( "static" ) );
  Token::KeywordsTable.insert( Symbol( "struct" ) );
  Token::KeywordsTable.insert( Symbol( "switch" ) );
  Token::KeywordsTable.insert( Symbol( "typedef" ) );
  Token::KeywordsTable.insert( Symbol( "union" ) );
  Token::KeywordsTable.insert( Symbol( "unsigned" ) );
  Token::KeywordsTable.insert( Symbol( "void" ) );
  Token::KeywordsTable.insert( Symbol( "volatile" ) );
  Token::KeywordsTable.insert( Symbol( "while" ) );
  Token::KeywordsTable.insert( Symbol( "_Alignas" ) );
  Token::KeywordsTable.insert( Symbol( "_Alignof" ) );
  Token::KeywordsTable.insert( Symbol( "_Atomic" ) );
  Token::KeywordsTable.insert( Symbol( "_Bool" ) );
  Token::KeywordsTable.insert( Symbol( "_Complex" ) );
  Token::KeywordsTable.insert( Symbol( "_Generic" ) );
  Token::KeywordsTable.insert( Symbol( "_Imaginary" ) );
  Token::KeywordsTable.insert( Symbol( "_Noreturn" ) );
  Token::KeywordsTable.insert( Symbol( "_Static_assert" ) );
  Token::KeywordsTable.insert( Symbol( "_Thread_local" ) );
}

std::ostream & Lex::operator<<( std::ostream &out, Token const &tok )
{
  switch ( tok.kind )
  {
    case TK::KEYWORD:         out << "keyword"; break;
    case TK::IDENTIFIER:      out << "identifier"; break;
    case TK::CONSTANT:        out << "constant"; break;
    case TK::STRING_LITERAL:  out << "string-literal"; break;
    case TK::END_OF_FILE:     out << "end-of-file"; return out;
    default:                  out << "punctuator";
  }
  out << " " << tok.sym;
  return out;
}

void Token::dump() const
{
  std::cout << *this << std::endl;
}
