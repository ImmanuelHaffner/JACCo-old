//===--- Parser.cc --------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements the Parser interface.
//
//===----------------------------------------------------------------------===//

#include "Parser.h"

using namespace C4;
using namespace AST;
using namespace Parse;
using namespace Lex;


/*
 *
 * Parser Main Functions
 *
 */

Parser::Parser( Lexer &lexer ) : lexer( lexer ) {}

Parser::~Parser() {}

ASTNode & Parser::parse()
{
  return parseUnaryExpression();
}
