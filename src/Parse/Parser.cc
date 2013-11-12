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
  _accept( t );
  lexer.get();
}

bool Parser::_accept( TokenKind tKind )
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

bool Parser::_accept( KeywordKind keyword )
{
  if ( ! _accept( TokenKind::KEYWORD ) )
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

bool Parser::_accept( PunctuatorKind punctuator )
{
  if ( ! _accept( TokenKind::PUNCTUATOR ) )
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

    case TokenKind::PUNCTUATOR:
      {
        PunctuatorToken &p = static_cast< PunctuatorToken & >( tok );
        if ( p.punctuator == PunctuatorKind::LPAR )
        {
          lexer.get();
          ASTNode & expr = parseExpression();
          
            Token &tok2 = lexer.peek();
            if ( tok2.kind == TokenKind::PUNCTUATOR )
            {
              PunctuatorToken &p2 = static_cast< PunctuatorToken & >( tok2 );
              if ( p2.punctuator == PunctuatorKind::RPAR )
              {
                ASTNode * e = new ASTNode( ASTType::PRIMARY_EXPRESSION );
              }
            }
        }
      }

    default:;
  }
  // ERROR:
  return *( new ASTNode( ASTType::ILLEGAL ) );
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
  Token &tok = lexer.peek();

  if ( tok.kind == TokenKind::PUNCTUATOR )
  {
    PunctuatorToken &p = static_cast< PunctuatorToken & >( tok );

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
  }
  // ERROR:
  return *( new ASTNode( ASTType::ILLEGAL ) );
}

ASTNode & Parser::parseExpression()
{
}
