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
#include "../Lex/PunctuatorToken.h"
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
    oss << "unexpected " << tok << ", expected ";
    auto res = TokenKindNames.find( tKind );
    oss << res->second;

    errorf( tok.pos, "%s", oss.str().c_str() );
    return false;
  }
  return true;
}

bool Parser::match( KeywordKind keyword )
{
  if ( ! match( TokenKind::KEYWORD ) )
    return false;

  KeywordToken &kTok = static_cast< KeywordToken & >( lexer.peek() );
  if ( keyword != kTok.keyword )
  {
    std::ostringstream oss;
    oss << "unexpected keyword '" << kTok.text << "', expected ";
    auto res = KeywordKindNames.find( kTok.keyword );
    oss << res->second;

    errorf( kTok.pos, "%s", oss.str().c_str() );
    return false;
  }
  return true;
}

bool Parser::match( PunctuatorKind punctuator )
{
  if ( ! match( TokenKind::PUNCTUATOR ) )
    return false;

  PunctuatorToken &pTok = static_cast< PunctuatorToken & >( lexer.peek() );
  if ( punctuator != pTok.punctuator )
  {
    std::ostringstream oss;
    oss << "unexpected punctuator '" << pTok.text << "', expected ";
    auto res = PunctuatorKindNames.find( pTok.punctuator );
    oss << res->second;

    errorf( pTok.pos, "%s", oss.str().c_str() );
    return false;
  }
  return true;
}

bool Parser::match( std::string const &s )
{
  return match( s.c_str() );
}

bool Parser::match( char const * const s )
{
  Token &tok = lexer.peek();
  if ( tok.text != s )
  {
    std::ostringstream oss;
    oss << "unexpected input '" << tok.text << "', expected "
      << s;

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
  return parseIdentifier();
}

/*
 * Methods that parse particular parts of the grammar.
 */

ASTNode & Parser::parseIdentifier()
{
  match( TokenKind::IDENTIFIER );
  ASTNode & node = *( new Identifier(
        static_cast< IdentifierToken & >( lexer.peek() ) ) );
  lexer.get();
  return node;
}

ASTNode & Parser::parsePrimaryExpression()
{
  Token &tok = lexer.peek();

  switch ( tok.kind )
  {
    case TokenKind::IDENTIFIER:
      lexer.get();
      return *( new Identifier( static_cast< IdentifierToken & >( tok ) ) );

    case TokenKind::CONSTANT:
      lexer.get();
      return *( new Constant( static_cast< ConstantToken & >( tok ) ) );

    case TokenKind::STRING_LITERAL:
      lexer.get();
      return *( new StringLiteral( static_cast< StringLiteralToken & >( tok ) ) );

    default:
      {
        accept( PunctuatorKind::LPAR );
        ASTNode &expr = parseExpression();
        accept( PunctuatorKind::RPAR );

        ASTNode &node = *( new ASTNode( ASTType::PRIMARY_EXPRESSION ) );
        node.append( &expr );
        return node;
      }
  }
}

ASTNode & Parser::parseUnaryOperator()
{
  Token &tok = lexer.peek();

  if ( tok.kind == TokenKind::PUNCTUATOR )
  {
    PunctuatorToken &p = static_cast< PunctuatorToken & >( tok );

    switch ( p.punctuator )
    {
      case PunctuatorKind::AND:
      case PunctuatorKind::MUL:
      case PunctuatorKind::PLUS:
      case PunctuatorKind::MINUS:
      case PunctuatorKind::NEG:
      case PunctuatorKind::NOT:
        lexer.get();
        return *( new ASTNode( ASTType::UNARY_OPERATOR ) );

      default:;
    }
  }
  // ERROR:
  return *( new ASTNode( ASTType::ILLEGAL ) );
}

ASTNode & Parser::parseAssignmentOperator()
{
  if ( ! match( TokenKind::PUNCTUATOR ) )
  {
    return *( new ASTNode( ASTType::ILLEGAL ) );
  }

  PunctuatorToken &p = static_cast< PunctuatorToken & >( lexer.peek() );

  switch ( p.punctuator )
  {
    case PunctuatorKind::ASSIGN:
    case PunctuatorKind::MULASSIGN:
    case PunctuatorKind::DIVASSIGN:
    case PunctuatorKind::MODASSIGN:
    case PunctuatorKind::ADDASSIGN:
    case PunctuatorKind::SUBASSIGN:
    case PunctuatorKind::LSHIFTASSIGN:
    case PunctuatorKind::RSHIFTASSIGN:
    case PunctuatorKind::ANDASSIGN:
    case PunctuatorKind::XORASSIGN:
    case PunctuatorKind::ORASSIGN:
      lexer.get();
      return *( new ASTNode( ASTType::ASSIGNMENT_OPERATOR ) );

    default:;
  }
  // ERROR:
  return *( new ASTNode( ASTType::ILLEGAL ) );
}

ASTNode & Parser::parseExpression()
{
}

ASTNode & Parser::parseStorageClassSpecifier()
{
}
