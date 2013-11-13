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
#include "../AST/Identifier.h"
#include "../AST/Constant.h"
#include "../AST/StringLiteral.h"

using namespace C4;
using namespace AST;
using namespace Parse;
using namespace Lex;

/*
 *
 * Parser helper functions
 *
 */

  template < typename T >
void Parser::accept( T t )
{
  match( t );
  lexer.get();
}

bool Parser::match( TokenKind tKind )
{
  Token &tok = lexer.peek();
  if ( tKind != tok.kind )
  {
    std::ostringstream oss;
    oss << "unexpected token '" << tok << "', expected ";

    auto res = TokenKindNames.find( tok.kind );
    oss << res->second;

    errorf( tok.pos, "%s", oss.str().c_str() );
    return false;
  }
  return true;
}


/*
 *
 * Parser
 *
 */

Parser::Parser( Lexer &lexer ) : lexer( lexer ) {}

Parser::~Parser() {}

ASTNode & Parser::parse()
{

}

/*
 * Methods that parse particular parts of the grammar.
 */

ASTNode & Parser::parsePrimaryExpression()
{
  ASTNode & node = *( new ASTNode( ASTType::PRIMARY_EXPRESSION ) );

  Token &tok = lexer.peek();

  switch ( tok.kind )
  {
    case TokenKind::IDENTIFIER:
      lexer.get();
      node.append( new Identifier( tok ) );
      return node;

    case TokenKind::CONSTANT:
      lexer.get();
      node.append( new Constant( tok ) );
      return node;

    case TokenKind::STRING_LITERAL:
      lexer.get();
      node.append( new StringLiteral( tok ) );
      return node;

    case TokenKind::PUNCTUATOR:
      {
        if ( tok.text == "(" )
        {
          lexer.get();
          node.append( & parseExpression() );
          accept( ")" );
          return node;
        }
      }

    default:;
  }
  // ERROR:
  return *( new ASTNode( ASTType::ILLEGAL ) );
}

ASTNode & Parser::parseUnaryOperator()
{
  ASTNode & node = *( new ASTNode( ASTType::PRIMARY_EXPRESSION ) );

  Token &tok = lexer.peek();

  if ( tok.text == "&"
      || tok.text == "*"
      || tok.text == "+"
      || tok.text == "-"
      || tok.text == "~"
      || tok.text == "!" )
  {
    lexer.get();
    return node;
  }

  // ERROR:
  return *( new ASTNode( ASTType::ILLEGAL ) );
}

ASTNode & Parser::parseAssignmentOperator()
{
}

ASTNode & Parser::parseExpression()
{
}
