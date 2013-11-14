//===--- Parser.cc --------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements the Parser interface.
//
//===----------------------------------------------------------------------===//

#include "Parser.h"

#include <iostream>
#include <sstream>
#include "../diagnostic.h"

using namespace C4;
using namespace AST;
using namespace Parse;
using namespace Lex;


/*
 *
 * Parser Helper Functions
 *
 */

bool Parser::match( TokenKind tKind )
{
  if ( ! is( tKind ) )
  {
    Token &tok = lexer.peek();
    std::ostringstream oss;
    oss << "unexpected token '" << tok << "', expected ";

    auto res = TokenKindNames.find( tok.kind );
    oss << res->second;

    errorf( tok.pos, "%s", oss.str().c_str() );
    return false;
  }
  return true;
}

bool Parser::match( char const * const s )
{
  if ( ! is( s ) )
  {
    Token &tok = lexer.peek();
    std::ostringstream oss;
    oss << "unexpected '" << tok.text << "', expected '" << s << "'";
    errorf( tok.pos, "%s", oss.str().c_str() );
    return false;
  }
  return true;
}


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
