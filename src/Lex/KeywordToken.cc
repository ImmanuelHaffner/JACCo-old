//===--- KeywordToken.cc --------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the tokens.
//
//===----------------------------------------------------------------------===//

#include "KeywordToken.h"

#include "../Support/Diagnostic.h"

using namespace C4;
using namespace Lex;

std::ostream & Lex::operator<<( std::ostream &out, KeywordToken const &tok )
{
  out << tok.pos << " keyword " << tok.text;
  return out;
}

void KeywordToken::dump() const
{
  std::cout << *this;
}
