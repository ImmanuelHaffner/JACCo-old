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

std::ostream & Lex::operator<<( std::ostream &out, Token const &tok )
{
  switch ( tok.kind )
  {
    case TK::KEYWORD:         out << "keyword"; break;
    case TK::IDENTIFIER:      out << "identifier"; break;
    case TK::CONSTANT:        out << "constant"; break;
    case TK::STRING_LITERAL:  out << "string-literal"; break;
    case TK::END_OF_FILE:     out << "end-of-file"; break;
    default:                  out << "punctuator";
  }
  out << " " << tok.sym;
  return out;
}

void Token::dump() const
{
  std::cout << *this;
}
