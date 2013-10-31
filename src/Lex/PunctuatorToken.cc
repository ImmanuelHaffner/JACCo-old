//===--- PunctuatorToken.cc -----------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the tokens.
//
//===----------------------------------------------------------------------===//

#include "PunctuatorToken.h"

#include "../Support/Diagnostic.h"

using namespace C4;
using namespace Lex;

std::ostream & Lex::operator<<( std::ostream &out, PunctuatorToken const &tok )
{
  out << tok.pos << " punctuator " << tok.text;
  return out;
}

void PunctuatorToken::dump() const
{
  std::cout << *this;
}
