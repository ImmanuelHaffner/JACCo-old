//===--- Parser.cc --------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements the Parser interface.
//
//===----------------------------------------------------------------------===//

#include "Parser.h"

using namespace C4;
using namespace Parse;
using namespace Lex;
using namespace AST;


/*
 *
 * Parser Main Functions
 *
 */

Parser::Parser( Lexer &lexer ) : lexer(lexer), current(NULL), next(NULL) {}

Parser::~Parser() {}

void Parser::getNextToken()
{
  if ( current ) delete current;
  current = next;
  next = new Lex::Token( lexer.getToken() );
}

void Parser::parse()
{
  getNextToken();
  getNextToken();
  parseUnaryExpression();
}

//===----------------------------------------------------------------------===//
//
//  Parser Sub Functions
//
//  These functions parse particular rules of the grammar, e.g.
//  declarations or expressions.
//
//===----------------------------------------------------------------------===//

Expression & Parser::parseExpression()
{
  Expression &lhs = parsePrimaryExpression();
  return parseBinOpRHS( 0, lhs );
}

Expression & Parser::parsePrimaryExpression()
{
  Expression * expr = NULL;
  switch( current->kind )
  {
    case TK::IDENTIFIER:
      expr = new Variable( *current ); getNextToken(); break;

    case TK::CONSTANT:
      expr = new Constant( *current ); getNextToken(); break;

    case TK::STRING_LITERAL:
      expr = new StringLiteral( *current ); getNextToken(); break;

    case TK::LPar:
      getNextToken(); // consume '('
      expr = & parseExpression();
      accept( TK::RPar );
      break;

    default:
      errorf( current->pos, "%s",
          "identifier, constant, string-literal or '(' expr ')' expected" );
      expr = new IllegalExpression();
  }

  return *expr;
} // end parsePrimaryExpression

Expression & Parser::parseUnaryExpression()
{
  switch ( current->kind )
  {
    case TK::IncOp:
    case TK::DecOp:
      {
        Token op( *current );
        getNextToken();
        return *( new UnaryExpression( op, parseUnaryExpression() ) );
      }

    case TK::Sizeof:
      {
        break;
        if ( next->kind == TK::LPar )
        {
          getNextToken();
          // TODO parse type name
          accept( TK::RPar );
          break;
        }
        Token op( *current );
        return *( new UnaryExpression( op, parseUnaryExpression() ) );
      }

    default:;
  }
  errorf( current->pos, "%s", "unary expression expected" );
  return *( new IllegalExpression() );
}

Expression & Parser::parseBinOpRHS( int exprPrec, AST::Expression &lhs )
{
  int tokPrec = getTokenPrecedence();

  // If this binary expression binds less than lhs, we are done.
  if ( tokPrec < exprPrec )
    return lhs;

  Token const * binOp = this->current;
  getNextToken(); // eat BinOp

  Expression &rhs = parsePrimaryExpression();

  // If binOp binds less with the RHS than the operator after RHS, let the
  // pending operator take RHS as its LHS.
  int nextPrec = getTokenPrecedence();
  if ( tokPrec < nextPrec )
    return *( new BinaryExpression( *binOp, lhs,
          parseBinOpRHS( tokPrec + 1, rhs ) ) );

  return *( new BinaryExpression( *binOp, lhs, rhs ) );
} // end parseBinOpRHS
