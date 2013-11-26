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

void Parser::readNextToken()
{
  if ( current ) delete current;
  current = next;
  next = new Lex::Token( lexer.getToken() );
}

void Parser::parse()
{
  readNextToken();
  readNextToken();
  parseExpression();
}


//===----------------------------------------------------------------------===//
//
//  Parser Sub Functions
//
//  These functions parse particular rules of the grammar, e.g.
//  declarations or expressions.
//
//===----------------------------------------------------------------------===//

//
//  Expressions
//

Expression & Parser::parsePrimaryExpression()
{
  Expression * expr = NULL;
  switch( current->kind )
  {
    case TK::IDENTIFIER:
      expr = new Variable( *current ); readNextToken(); break;

    case TK::CONSTANT:
      expr = new Constant( *current ); readNextToken(); break;

    case TK::STRING_LITERAL:
      expr = new StringLiteral( *current ); readNextToken(); break;

    case TK::LPar:
      {
        readNextToken(); // eat '('
        parseExpression();
        accept( TK::RPar ); // eat ')'
        break;
      }

    default:
      {
        std::ostringstream oss;
        oss << current->kind;
        errorf( current->pos, "%s - %s", oss.str().c_str(),
            "identifier, constant, string-literal or '(' expression ')' "
            "expected" );
        expr = new IllegalExpression();
      }
  }

  return *expr;
} // end parsePrimaryExpression

Expression & Parser::parsePostfixExpression()
{
  parsePrimaryExpression();

  for (;;)
  {
    switch ( current->kind )
    {
      case TK::LBracket:
        {
          readNextToken(); // eat '['
          parseExpression();
          accept( TK::RBracket ); // eat ']'
          break;
        }

      case TK::LPar:
        {
          readNextToken(); // eat '('
          if ( current->kind != TK::RPar )
            parseArgumentExpressionList();
          accept( TK::RPar ); // eat ')'
          break;
        }

      case TK::PtrOp:
      case TK::Dot:
        {
          readNextToken(); // eat operator
          accept( TK::IDENTIFIER ); // eat Identifier
          break;
        }

      case TK::IncOp:
      case TK::DecOp:
        {
          readNextToken(); // eat operator
          break;
        }

      default: goto for_end0; // exit loop
    } // end switch
  } // end for
for_end0:
  return *( new IllegalExpression() );
} // end parsePostfixExpression

Expression & Parser::parseArgumentExpressionList()
{
  parseAssignmentExpression();
  while ( current->kind == TK::Comma )
    parseAssignmentExpression();
  return *( new IllegalExpression() );
}

Expression & Parser::parseUnaryExpression()
{
  switch ( current->kind )
  {
    case TK::IncOp:
    case TK::DecOp:
      {
        readNextToken(); // eat operator
        parseUnaryExpression();
        break;
      }

    case TK::Sizeof:
      {
        readNextToken(); // eat 'sizeof'
        if ( next->kind == TK::LPar )
        {
          readNextToken(); // eat '('
          parseTypeName();
          accept( TK::RPar ); // eat ')'
        }
        else
          parseUnaryExpression();
        break;
      }

    case Lex::TK::And:
    case Lex::TK::Mul:
    case Lex::TK::Plus:
    case Lex::TK::Minus:
    case Lex::TK::Neg:
    case Lex::TK::Not:
      {
        readNextToken(); // eat unary operator
        parseCastExpression();
        break;
      }

    default:
      return parsePostfixExpression();
  }
  return *( new IllegalExpression() );
} // end parseUnaryExpression

Expression & Parser::parseCastExpression()
{
  while ( current->kind == TK::LPar )
  {
    readNextToken(); // eat '('
    parseTypeName();
    accept( TK::RPar ); // eat ')'
  }
  parseUnaryExpression();
  return *( new IllegalExpression() );
} // end parseCastExpression

Expression & Parser::parseBinaryExpression()
{
  Expression &lhs = parseCastExpression();
  return parseBinOpRHS( 0, lhs );
} // end parseBinaryExpression

Expression & Parser::parseBinOpRHS( int exprPrec, AST::Expression &lhs )
{
  int tokPrec = getTokenPrecedence();

  // If this binary expression binds less than lhs, we are done.
  if ( tokPrec < exprPrec )
    return lhs;

  Token const * binOp = this->current;
  readNextToken(); // eat BinOp

  Expression &rhs = parseCastExpression();

  // If binOp binds less with the RHS than the operator after RHS, let the
  // pending operator take RHS as its LHS.
  int nextPrec = getTokenPrecedence();
  if ( tokPrec < nextPrec )
    return *( new BinaryExpression( *binOp, lhs,
          parseBinOpRHS( tokPrec + 1, rhs ) ) );

  return *( new BinaryExpression( *binOp, lhs, rhs ) );
} // end parseBinOpRHS

Expression & Parser::parseConditionalExpression()
{
  parseBinaryExpression();

  if ( current->kind == TK::QMark )
  {
    readNextToken(); // eat '?'
    parseExpression();
    accept( TK::Col ); // eat ':'
    parseConditionalExpression();
  }

  return *( new IllegalExpression() );
} // end parseConditionalExpression

/// Note: we diverge from the ANSI-C grammar when parsing the
/// assignment-expression production. ANSI-C specifies that the LHS of an
/// assignment operator should be parsed as a unary-expression, but consistency
/// dictates that it be a conditional-expession. In practice, the important
/// thing here is that the LHS of an assignment has to be an l-value, which
/// productions between unary-expression and conditional-expression don't
/// produce. Because we want consistency, we parse the LHS as a
/// conditional-expression, then check for l-value-ness in semantic analysis
/// stages.
Expression & Parser::parseAssignmentExpression()
{
  parseConditionalExpression();

  for (;;)
  {
    switch ( current->kind )
    {
      case TK::Assign:
      case TK::MulAssign:
      case TK::DivAssign:
      case TK::ModAssign:
      case TK::AddAssign:
      case TK::SubAssign:
      case TK::LShiftAssign:
      case TK::RShiftAssign:
      case TK::AndAssign:
      case TK::XorAssign:
      case TK::OrAssign:
        readNextToken(); // eat assignment-operator
        parseConditionalExpression();

      default:
        goto for_end1;
    }
  }
for_end1:
  return *( new IllegalExpression() );
} // end parseAssignmentExpression

Expression & Parser::parseExpression()
{
  parseAssignmentExpression();

  while ( current->kind == TK::Comma )
  {
    readNextToken(); // eat ','
    parseAssignmentExpression();
  }

  return *( new IllegalExpression() );
} // end parseExpression


//
//  Declarations
//

Declaration & Parser::parseDeclaration()
{
  parseDeclarationSpecifiers();
  if ( current->kind != TK::SCol )
    parseInitDeclaratorList();
  accept( TK::SCol ); // eat ';'
  return *( new IllegalDeclaration() );
} // end parseDeclaration

Declaration & Parser::parseDeclarationSpecifiers()
{
  parseTypeSpecifier();
  while ( is( TK::Void, TK::Char, TK::Int, TK::Struct ) )
    parseTypeSpecifier();
  return *( new IllegalDeclaration() );
} // end parseDeclarationSpecifiers

Declaration & Parser::parseInitDeclaratorList()
{
  parseInitDeclarator();
  while ( current->kind == TK::Comma )
  {
    readNextToken();
    parseInitDeclarator();
  }
  return *( new IllegalDeclaration() );
} // end parseInitDeclaratorList

Declaration & Parser::parseInitDeclarator()
{
  parseDeclarator();
  // Our C subset elides initialization
  return *( new IllegalDeclaration() );
} // end parseInitDeclarator

Declaration & Parser::parseTypeSpecifier()
{
  switch ( current->kind )
  {
    case TK::Void:
    case TK::Char:
    case TK::Int:
      readNextToken();
      break;

    case TK::Struct:
      parseStructOrUnionSpecifier();
      break;

    default:
      {
        std::ostringstream oss;
        oss << current->kind;
        errorf( current->pos, "%s - %s", oss.str().c_str(),
            "'void', 'char', 'int' or 'struct' expected" );
      }
  }
  return *( new IllegalDeclaration() );
} // end parseTypeSpecifier

Declaration & Parser::parseStructOrUnionSpecifier()
{
  parseStructOrUnion();
  switch ( current->kind )
  {
    case TK::IDENTIFIER:
      readNextToken(); // eat identifier
      if ( current->kind == TK::LBrace )
      {
        readNextToken(); // eat '{'
        parseStructDeclarationList();
        accept( TK::RBrace ); // eat '}'
      }
      break;

    case TK::LBrace:
      readNextToken(); // eat '{'
      parseStructDeclarationList();
      accept( TK::RBrace ); // eat '}'
      break;

    default:
      {
        std::ostringstream oss;
        oss << current->kind;
        errorf( current->pos, "%s - %s", oss.str().c_str(),
            "identifier or '{' expected" );
      }
  }
  return *( new IllegalDeclaration() );
} // end parseStructOrUnionSpecifier

Declaration & Parser::parseStructOrUnion()
{
  switch ( current->kind )
  {
    // Our C subset elides unions.
    case TK::Struct:
      readNextToken();
      break;

    default:
      {
        std::ostringstream oss;
        oss << current->kind;
        errorf( current->pos, "%s - %s", oss.str().c_str(),
            "'struct' expected" );
      }
  }
  return *( new IllegalDeclaration() );
} // end parseStructOrUnion

Declaration & Parser::parseStructDeclarationList()
{
  do
  {
    parseStructDeclaration();
  }
  while ( current->kind != TK::RBrace );
  return *( new IllegalDeclaration() );
} // end parseStructDeclarationList

Declaration & Parser::parseStructDeclaration()
{
  parseSpecifierQualifierList();
  parseStructDeclaratorList();
  accept( TK::SCol ); // eat ';'
  return *( new IllegalDeclaration() );
} // end parseStructDeclaration

Declaration & Parser::parseSpecifierQualifierList()
{
  parseTypeSpecifier();

  for (;;)
  {
    switch ( current->kind )
    {
      case TK::Void:
      case TK::Char:
      case TK::Int:
      case TK::Struct:
        parseTypeSpecifier();
        break;

        // Our C subset elides any other type specifier or qualifier.

      default: goto for_end2;
    }
  }
for_end2:
  return *( new IllegalDeclaration() );
} // end parseSpecifierQualifierList

Declaration & Parser::parseStructDeclaratorList()
{
  parseStructDeclarator();
  while ( current->kind == TK::Comma )
  {
    readNextToken(); // eat ','
    parseStructDeclarator();
  }
  return *( new IllegalDeclaration() );
} // end parseStructDeclaratorList

Declaration & Parser::parseStructDeclarator()
{
  if ( current->kind == TK::Col )
  {
    readNextToken(); // eat ':'
    parseConstantExpression();
  }
  else
  {
    parseDeclarator();
    if ( current->kind == TK::Col )
    {
      readNextToken(); // eat ':'
      parseConstantExpression();
    }
  }
  return *( new IllegalDeclaration() );
} // end parseStructDeclarator

Declaration & Parser::parseDeclarator()
{
  if ( current->kind == TK::Mul )
    parsePointer();
  parseDirectDeclarator();
  return *( new IllegalDeclaration() );
} // end parseDeclarator

Declaration & Parser::parseDirectDeclarator()
{
  switch ( current->kind )
  {
    case TK::IDENTIFIER:
      readNextToken(); // eat identifier
      break;

    case TK::LPar:
      readNextToken(); // eat '('
      parseDeclarator();
      accept( TK::RPar ); // eat ')'
      break;

    default:
      {
        std::ostringstream oss;
        oss << current->kind;
        errorf( current->pos, "%s - %s", oss.str().c_str(),
            "identifier or '(' expected" );
      }
  } // end switch

  for (;;)
  {
    switch ( current->kind )
    {
      case TK::LBracket:
        {
          readNextToken(); // eat '['
          if ( current->kind != TK::RBracket )
            parseConstantExpression();
          accept( TK::RBracket ); // eat ']'
          break;
        }

      case TK::LPar:
        {
          readNextToken(); // eat '('
          switch ( current->kind )
          {
            case TK::RPar:
              break;

            case TK::IDENTIFIER:
              parseIdentifierList();
              break;

            case TK::Void:
            case TK::Char:
            case TK::Int:
            case TK::Struct:
              parseParameterTypeList();
              break;

            default:
              {
                std::ostringstream oss;
                oss << current->kind;
                errorf( current->pos, "%s - %s", oss.str().c_str(),
                    "identifier, 'void', 'char', 'int', 'struct' or ')' "
                    "expected" );
              }
          }
          accept( TK::RPar ); // eat ')'
          break;
        }

      default: goto for_end3;
    } // end switch
  } // end for
for_end3:
  return *( new IllegalDeclaration() );
} // end parseDirectDeclarator

Declaration & Parser::parsePointer()
{
  accept( TK::Mul ); // '*'
  while ( current->kind == TK::Mul )
    readNextToken(); // eat '*'
  return *( new IllegalDeclaration() );
} // end parsePointer

Declaration & Parser::parseParameterTypeList()
{
  parseParameterList();
  // NOTE: Our C subset elides the ellipsis
  return *( new IllegalDeclaration() );
} // end parseParameterTypeList

Declaration & Parser::parseParameterList()
{
  parseParameterDeclaration();
  while ( current->kind == TK::Comma )
  {
    readNextToken(); // eat ','
    parseParameterDeclaration();
  }
  return *( new IllegalDeclaration() );
} // end parseParameterList

Declaration & Parser::parseParameterDeclaration()
{
  parseDeclarationSpecifiers();
  switch ( current->kind )
  {
    case TK::IDENTIFIER:
      parseDeclarator();
      break;

    case TK::Mul:
    case TK::LPar:
    case TK::LBracket:
      parseMaybeAbstractDeclarator();
      break;

    default:;
  }
  return *( new IllegalDeclaration() );
} // end parseParameterDeclaration

Declaration & Parser::parseIdentifierList()
{
  for (;;)
  {
    if ( current->kind == TK::IDENTIFIER )
      readNextToken(); // eat identifier
    if ( current->kind == TK::Comma )
      readNextToken(); // eat ','
    else
      break;
  }
  return *( new IllegalDeclaration() );
} // end parseIdentifierList

Declaration & Parser::parseTypeName()
{
  parseSpecifierQualifierList();

  switch ( current->kind )
  {
    case TK::Mul:
    case TK::LPar:
    case TK::LBracket:
      parseAbstractDeclarator();
      break;

    default:;
  }
  return *( new IllegalDeclaration() );
} // end parseTypeName

Declaration & Parser::parseAbstractDeclarator()
{
  switch ( current->kind )
  {
    case TK::Mul:
      parsePointer();
      switch ( current->kind )
      {
        case TK::LPar:
        case TK::LBracket:
          parseDirectAbstractDeclarator();
          break;

        default:;
      } // end switch
      break;

    case TK::LPar:
    case TK::LBracket:
      parseDirectAbstractDeclarator();
      break;

    default:
      {
        std::ostringstream oss;
        oss << current->kind;
        errorf( current->pos, "%s - %s", oss.str().c_str(),
            "'*', '(', or '[' expected" );
      }
  } // end switch
  return *( new IllegalDeclaration() );
} // end parseAbstractDeclarator

Declaration & Parser::parseDirectAbstractDeclarator()
{
  switch ( current->kind )
  {
    case TK::LPar:
      readNextToken(); // eat '('
      switch ( current->kind )
      {
        case TK::RPar: break;

        case TK::Mul:
        case TK::LPar:
        case TK::LBracket:
          parseAbstractDeclarator();
          break;

        case TK::Void:
        case TK::Char:
        case TK::Int:
        case TK::Struct:
          parseParameterTypeList();
          break;

        default:
          {
            std::ostringstream oss;
            oss << current->kind;
            errorf( current->pos, "%s - %s", oss.str().c_str(),
                "'*', '(', '[', 'void', 'char', 'int', 'struct' or ')' "
                "expected" );
          }
      } // end switch
      accept( TK::RPar ); // eat ')'
      break;

    case TK::LBracket:
      readNextToken(); // eat '['
      if ( current->kind != TK::RBracket )
        parseConstantExpression();
      accept( TK::RBracket ); // eat ']'
      break;

    default:
      {
        std::ostringstream oss;
        oss << current->kind;
        errorf( current->pos, "%s - %s", oss.str().c_str(),
            "'(' or '[' expected" );
      }
  } // end switch

  for (;;)
  {
    switch ( current->kind )
    {
      case TK::LBracket:
        readNextToken(); // eat '['
        if ( current->kind != TK::RBracket )
          parseConstantExpression();
        accept( TK::RBracket ); // eat ']'
        break;

      case TK::LPar:
        readNextToken(); // eat '('
        if ( current->kind != TK::RPar )
          parseParameterTypeList();
        accept( TK::RPar );
        break;

      default: goto for_end4;
    } // end switch
  } // end for
for_end4:
  return *( new IllegalDeclaration() );
} // end parseDirectAbstractDeclarator

Declaration & Parser::parseMaybeAbstractDeclarator()
{
  switch ( current->kind )
  {
    case TK::Mul:
      parsePointer();
      switch ( current->kind )
      {
        case TK::IDENTIFIER:
          parseDirectDeclarator();
          break;

        case TK::LBracket:
          parseDirectAbstractDeclarator();
          break;

        case TK::LPar:
          parseDirectMaybeAbstractDeclarator();
          break;

        default:;
      } // end switch
      break;

    case TK::IDENTIFIER:
      parseDirectDeclarator();
      break;

    case TK::LBracket:
      parseDirectAbstractDeclarator();
      break;

    case TK::LPar:
      parseDirectMaybeAbstractDeclarator();
      break;

    default:
      {
        std::ostringstream oss;
        oss << current->kind;
        errorf( current->pos, "%s - %s", oss.str().c_str(),
            "identifier, '*', '(' or '[' expected" );
      }
  } // end switch

  return *( new IllegalDeclaration() );
} // end parseMaybeAbstractDeclarator

Declaration & Parser::parseDirectMaybeAbstractDeclarator()
{
  assert( current->kind == TK::LPar &&
      "correct decision should have been taken by the caller" );
  readNextToken(); // eat '('
  switch ( current->kind )
  {
    case TK::RPar:
      break;

    case TK::Mul:
    case TK::IDENTIFIER:
    case TK::LPar:
    case TK::LBracket:
      parseMaybeAbstractDeclarator();
      break;

    case TK::Void:
    case TK::Char:
    case TK::Int:
    case TK::Struct:
      parseParameterTypeList();
      break;

    default:
      {
        std::ostringstream oss;
        oss << current->kind;
        errorf( current->pos, "%s - %s", oss.str().c_str(),
            "'*', '(', '[', 'void', 'char', 'int' or 'struct' expected" );
      }
  } // end switch
  return *( new IllegalDeclaration() );
} // end parseDirectMaybeAbstractDeclarator

Declaration & Parser::parseInitializer()
{
  switch ( current->kind )
  {
    case TK::LBrace:
      readNextToken(); // eat '{'
      parseInitializerList();
      if ( current->kind == TK::Comma )
        readNextToken(); // eat ','
      accept( TK::RBrace ); // eat '}'
      break;

    default:
      // TODO add cases for first-set of assignment expression
      parseAssignmentExpression();
  }
  return *( new IllegalDeclaration() );
} // end parseInitializer


Declaration & Parser::parseInitializerList()
{
  parseInitializer();
  while ( current->kind == TK::Comma )
  {
    readNextToken(); // eat ','
    parseInitializer();
  }
  return *( new IllegalDeclaration() );
} // end parseInitializerList

Statement & Parser::parseStatement()
{
  return *( new IllegalStatement() );
}
