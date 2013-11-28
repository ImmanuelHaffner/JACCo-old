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

//===------------------------------------------------------------------===//
//
//  Parser Helper Functions
//
//===------------------------------------------------------------------===//

void Parser::readNextToken()
{
  if ( current ) delete current;
  current = next;
  next = new Lex::Token( lexer.getToken() );
}

static inline void printTK( std::ostream &out, TK const tk )
{
  switch ( tk )
  {
    case Lex::TK::IDENTIFIER:
    case Lex::TK::CONSTANT:
    case Lex::TK::STRING_LITERAL:
    case Lex::TK::END_OF_FILE:
      out << tk;
      break;

    default:
      out << "'" << tk << "'";
  }
}

static inline void printTok( std::ostream &out, Token const &tok )
{
  printTK( out, tok.kind );
  switch ( tok.kind )
  {
    case TK::IDENTIFIER:
    case Lex::TK::CONSTANT:
    case Lex::TK::STRING_LITERAL:
      out << " '" << tok.sym << "'";

    default:;
  }
}

static inline void printTok( std::ostream &out, Token const * const tok )
{
  printTok( out, *tok );
}

/// If the current token is of kind tk, i.e. a call to is( tk ) would
/// return true, gets the next token, otherwise prints an error message.
void Parser::accept( Lex::TK tk )
{
  if ( ! is( tk ) )
  {
    std::ostringstream expected;
    printTK( expected, tk );

    std::ostringstream actual;
    printTok( actual, current );

    errorf( current->pos, "expected %s before %s", expected.str().c_str(),
        actual.str().c_str() );
  }
  else
    readNextToken(); // eat token
} // end accept
// End Parser Helper Functions


void Parser::parse()
{
  readNextToken();
  readNextToken();
  parseTranslationUnit();
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
      expr = new Variable( *current );
      readNextToken(); // eat identifier
      break;

    case TK::CONSTANT:
      expr = new Constant( *current );
      readNextToken(); // eat constant
      break;

    case TK::STRING_LITERAL:
      expr = new StringLiteral( *current );
      readNextToken(); // eat string-literal
      break;

    case TK::LPar:
      {
        readNextToken(); // eat '('
        parseExpression();
        accept( TK::RPar ); // eat ')'
        break;
      }

    default:
      {
        std::ostringstream actual;
        printTok( actual, current );

        errorf( current->pos, "expected %s before %s",
            "identifier, constant, string-literal or '(' expression ')'",
            actual.str().c_str() );
        expr = new IllegalExpression();
      }
  } // end switch

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

      default: goto for_end; // exit loop
    } // end switch
  } // end for
for_end:
  return *( new IllegalExpression() );
} // end parsePostfixExpression

Expression & Parser::parseArgumentExpressionList()
{
  parseAssignmentExpression();
  while ( current->kind == TK::Comma )
    parseAssignmentExpression();
  return *( new IllegalExpression() );
} // end parseArgumentExpressionList

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
        goto for_end;
    }
  }
for_end:
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
        std::ostringstream actual;
        printTok( actual, current );

        errorf( current->pos, "expected %s before %s",
            "type-specifier ('void', 'char', 'int' or 'struct')",
            actual.str().c_str() );
      }
  } // end switch
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
        std::ostringstream actual;
        printTok( actual, current );

        errorf( current->pos, "expected %s before %s",
            "identifier or '{' struct-declaration-list '}'",
            actual.str().c_str() );
      }
  } // end switch
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
        std::ostringstream actual;
        printTok( actual, current );

        errorf( current->pos, "expected %s before %s",
            "'struct'", actual.str().c_str() );
      }
  } // end switch
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

      default: goto for_end;
    }
  }
for_end:
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
        std::ostringstream actual;
        printTok( actual, current );

        errorf( current->pos, "expected %s before %s",
            "identifier or '(' declarator ')'", actual.str().c_str() );
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
        }
        break;

      case TK::LPar:
        {
          readNextToken(); // eat '('
          switch ( current->kind )
          {
            case TK::IDENTIFIER:
              parseIdentifierList();
              break;

            case TK::Void:
            case TK::Char:
            case TK::Int:
            case TK::Struct:
              parseParameterTypeList();
              break;

            default:;
          } // end switch
          accept( TK::RPar ); // eat ')'
        }
        break;

      default: goto for_end;
    } // end switch
  } // end for
for_end:
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
        std::ostringstream actual;
        printTok( actual, current );

        errorf( current->pos, "expected %s before %s",
            "'*' or direct-abstract-declarator", actual.str().c_str() );
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
        case TK::RPar:
          break;

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
            std::ostringstream actual;
            printTok( actual, current );

            errorf( current->pos, "expected %s before %s",
                "abstract-declarator or parameter-type-list",
                actual.str().c_str() );
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
        std::ostringstream actual;
        printTok( actual, current );

        errorf( current->pos, "expected %s before %s",
            "'(' [abstract-declarator|parameter-type-list] ')' or "
            "'[' [constant-expression] ']'",
            actual.str().c_str() );
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

      default: goto for_end;
    } // end switch
  } // end for
for_end:
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
        std::ostringstream actual;
        printTok( actual, current );

        errorf( current->pos, "expected %s before %s",
            "'*', identifier, '(' [abstract-]declarator|parameter-type-list ')'"
            " or '[' [constant-expression] ']' expected",
            actual.str().c_str() );
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
        std::ostringstream actual;
        printTok( actual, current );

        errorf( current->pos, "expected %s before %s",
            "identifier, '(' [abstract-]declarator ')', "
            "'(' parameter-type-list ')' or "
            "'[' [constant-expression] ']'",
            actual.str().c_str() );
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

    case TK::IDENTIFIER:
    case TK::CONSTANT:
    case TK::STRING_LITERAL:
    case TK::Sizeof:
    case TK::IncOp:
    case TK::DecOp:
    case TK::Mul:
    case TK::And:
    case TK::LPar:
    case TK::Plus:
    case TK::Minus:
    case TK::Not:
    case TK::Neg:
      parseAssignmentExpression();
      break;

    default:
      {
        std::ostringstream actual;
        printTok( actual, current );

        errorf( current->pos, "expected %s before %s",
            "assignment-expression or '{' initializer-list [','] '}'",
            actual.str().c_str() );
      }
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
  switch ( current->kind )
  {
    case TK::IDENTIFIER:
      // labeled-statement or expression-statement
      if ( next->kind == TK::Col )
        parseLabeledStatement();
      else
        parseExpressionStatement();
      break;

    case TK::Case:
    case TK::Default:
      parseLabeledStatement();
      break;

    case TK::LBrace:
      parseCompoundStatement();
      break;

    case TK::If:
    case TK::Switch:
      parseSelectionStatement();
      break;

    case TK::For:
    case TK::While:
    case TK::Do:
      parseIterationStatement();
      break;

    case TK::Goto:
    case TK::Break:
    case TK::Continue:
    case TK::Return:
      parseJumpStatement();
      break;

    case TK::CONSTANT:
    case TK::STRING_LITERAL:
    case TK::SCol:
    case TK::Sizeof:
    case TK::IncOp:
    case TK::DecOp:
    case TK::Mul:
    case TK::And:
    case TK::LPar:
    case TK::Plus:
    case TK::Minus:
    case TK::Not:
    case TK::Neg:
      parseExpressionStatement();
      break;

    default:
      {
        std::ostringstream actual;
        printTok( actual, current );

        errorf( current->pos, "expected %s before %s",
            "statement", actual.str().c_str() );
      }
  } // end switch
  return *( new IllegalStatement() );
} // end parseStatement

Statement & Parser::parseLabeledStatement()
{
  switch ( current->kind )
  {
    case TK::IDENTIFIER:
      readNextToken(); // eat identifier
      accept( TK::Col ); // eat ':'
      parseStatement();
      break;

    case TK::Case:
      readNextToken(); // eat 'case'
      parseConstantExpression();
      accept( TK::Col ); // eat ':'
      parseStatement();
      break;

    case TK::Default:
      readNextToken(); // eat 'default'
      accept( TK::Col ); // eat ':'
      parseStatement();
      break;

    default:
      {
        std::ostringstream actual;
        printTok( actual, current );

        errorf( current->pos, "expected %s before %s",
            "identifier, 'case' or 'default'", actual.str().c_str() );
      }
  } // end switch
  return *( new IllegalStatement() );
} // end parseLabeledStatement

Statement & Parser::parseCompoundStatement()
{
  accept( TK::LBrace ); // eat '{'
  switch ( current->kind )
  {
    case TK::RBrace:
      break;

    case TK::Void:
    case TK::Char:
    case TK::Int:
    case TK::Struct:
      parseDeclarationList();
      switch ( current->kind )
      {
        case TK::IDENTIFIER:
        case TK::CONSTANT:
        case TK::STRING_LITERAL:
        case TK::Goto:
        case TK::If:
        case TK::For:
        case TK::While:
        case TK::Do:
        case TK::Break:
        case TK::Continue:
        case TK::Switch:
        case TK::Case:
        case TK::Default:
        case TK::IncOp:
        case TK::DecOp:
        case TK::Return:
        case TK::Sizeof:
        case TK::Not:
        case TK::Neg:
        case TK::And:
        case TK::Mul:
        case TK::Plus:
        case TK::Minus:
        case TK::LPar:
        case TK::LBrace:
        case TK::SCol:
          parseStatement();
          break;

        default:;
      } // end switch
      break;

    case TK::IDENTIFIER:
    case TK::CONSTANT:
    case TK::STRING_LITERAL:
    case TK::Goto:
    case TK::If:
    case TK::For:
    case TK::While:
    case TK::Do:
    case TK::Break:
    case TK::Continue:
    case TK::Switch:
    case TK::Case:
    case TK::Default:
    case TK::IncOp:
    case TK::DecOp:
    case TK::Return:
    case TK::Sizeof:
    case TK::Not:
    case TK::Neg:
    case TK::And:
    case TK::Mul:
    case TK::Plus:
    case TK::Minus:
    case TK::LPar:
    case TK::LBrace:
    case TK::SCol:
      parseStatementList();
      break;

    default:
      {
        std::ostringstream actual;
        printTok( actual, current );

        errorf( current->pos, "expected %s before %s",
            "declaration or statement", actual.str().c_str() );
      }
  } // end switch
  accept( TK::RBrace ); // eat '}'
  return *( new IllegalStatement() );
} // end parseCompoundStatement

Statement & Parser::parseDeclarationList()
{
  parseDeclaration();

  for (;;)
  {
    switch ( current->kind )
    {
      case TK::Void:
      case TK::Char:
      case TK::Int:
      case TK::Struct:
        parseDeclaration();
        break;

      default: goto for_end;
    }
  } // end for
for_end:
  return *( new IllegalStatement() );
} // end parseDeclarationList

Statement & Parser::parseStatementList()
{
  parseStatement();

  for (;;)
  {
    switch ( current->kind )
    {
      case TK::IDENTIFIER:
      case TK::CONSTANT:
      case TK::STRING_LITERAL:
      case TK::Goto:
      case TK::If:
      case TK::For:
      case TK::While:
      case TK::Do:
      case TK::Break:
      case TK::Continue:
      case TK::Switch:
      case TK::Case:
      case TK::Default:
      case TK::IncOp:
      case TK::DecOp:
      case TK::Return:
      case TK::Sizeof:
      case TK::Not:
      case TK::Neg:
      case TK::And:
      case TK::Mul:
      case TK::Plus:
      case TK::Minus:
      case TK::LPar:
      case TK::LBrace:
      case TK::SCol:
        parseStatement();
        break;

      default: goto for_end;
    }
  } // end for
for_end:
  return *( new IllegalStatement() );
} // end parseStatementList

Statement & Parser::parseExpressionStatement()
{
  if ( current->kind != TK::SCol )
    parseExpression();
  accept( TK::SCol );
  return *( new IllegalStatement() );
} // end parseExpressionStatement

Statement & Parser::parseSelectionStatement()
{
  switch ( current->kind )
  {
    case TK::If:
      readNextToken(); // eat 'if'
      accept( TK::LPar ); // eat '('
      parseExpression();
      accept( TK::RPar ); // eat ')'
      parseStatement();
      if ( current->kind == TK::Else )
      {
        readNextToken(); // eat 'else'
        parseStatement();
      }
      break;

    case TK::Switch:
      readNextToken(); // eat 'switch'
      accept( TK::LPar ); // eat '('
      parseExpression();
      accept( TK::RPar ); // eat ')'
      parseStatement();
      break;

    default:
      {
        std::ostringstream actual;
        printTok( actual, current );

        errorf( current->pos, "expected %s before %s",
            "'if' or 'switch'", actual.str().c_str() );
      }
  } // end switch
  return *( new IllegalStatement() );
} // end parseSelectionStatement

Statement & Parser::parseIterationStatement()
{
  switch ( current->kind )
  {
    case TK::For:
      readNextToken(); // eat 'for'
      accept( TK::LPar ); // eat '('
      parseExpressionStatement(); // initialization
      parseExpressionStatement(); // condition
      if ( current->kind != TK::RPar )
        parseExpression(); // increment
      accept( TK::RPar ); // eat ')'
      parseStatement(); // body
      break;

    case TK::While:
      readNextToken(); // eat 'while'
      accept( TK::LPar ); // eat '('
      parseExpression(); // condition
      accept( TK::RPar ); // eat ')'
      parseStatement(); // body
      break;

    case TK::Do:
      readNextToken(); // eat 'do'
      parseStatement(); // body
      accept( TK::While ); // eat 'while'
      accept( TK::LPar ); // eat '('
      parseExpression(); // condition
      accept( TK::LPar ); // eat ')'
      break;

    default:
      {
        std::ostringstream actual;
        printTok( actual, current );

        errorf( current->pos, "expected %s before %s",
            "'for', 'do' or 'while'", actual.str().c_str() );
      }
  } // end switch
  return *( new IllegalStatement() );
} // end parseIterationStatement

Statement & Parser::parseJumpStatement()
{
  switch ( current->kind )
  {
    case TK::Goto:
      readNextToken(); // eat 'goto'
      accept( TK::IDENTIFIER ); // eat identifier
      accept( TK::SCol ); // eat ';'
      break;

    case TK::Continue:
      readNextToken(); // eat 'continue'
      accept( TK::SCol ); // eat ';'
      break;

    case TK::Break:
      readNextToken(); // eat 'break'
      accept( TK::SCol ); // eat ';'
      break;

    case TK::Return:
      readNextToken(); // eat 'return'
      if ( current->kind != TK::SCol )
        parseExpression();
      accept( TK::SCol ); // eat ';'
      break;

    default:
      {
        std::ostringstream actual;
        printTok( actual, current );

        errorf( current->pos, "expected %s before %s",
            "'return', 'continue', 'break' or 'goto'", actual.str().c_str() );
      }
  } // end switch
  return *( new IllegalStatement() );
} // end parseJumpStatement

Statement & Parser::parseTranslationUnit()
{
  do
  {
    // TODO stop or recover, if a corrupted external declaration was found
    Token const *prev = current;
    parseExternalDeclaration();
    if ( prev == current )
      readNextToken();
  }
  while ( current->kind != TK::END_OF_FILE );
  return *( new IllegalStatement() );
} // end parseTranslationUnit

Statement & Parser::parseExternalDeclaration()
{
  switch ( current->kind )
  {
    case TK::IDENTIFIER:
    case TK::Mul:
    case TK::LPar:
      // declarator
      parseDeclarator();
      switch ( current->kind )
      {
        case TK::Void:
        case TK::Char:
        case TK::Int:
        case TK::Struct:
          parseDeclarationList();
          break;

        default:;
      } // end switch
      parseCompoundStatement();
      break; // end declarator

    case TK::Void:
    case TK::Char:
    case TK::Int:
    case TK::Struct:
      // declaration-specifiers
      parseDeclarationSpecifiers();
      /*
       * Since init-declarator is defined as
       *    init-declarator:
       *      declarator
       *
       * we can simply check whether another init-declarator immediately
       * follows, to detect the init-declarator-list.
       *
       * If we later on allow assignments in init-declarator, we have to check,
       * whether the first parsed init-declarator actually contains an
       * assignment, or is just a declaration, such that we can decide for
       * init-declarator-list or just declarator.
       */

      // could contain an assignment, and such would be part of an
      // init-declarator-list
      parseInitDeclarator();

      switch ( current->kind )
      {
        case TK::SCol:
          // init-declarator-list
          readNextToken(); // eat ';'
          break;

        case TK::Comma:
          // init-declarator-list
          readNextToken(); // eat ','
          parseInitDeclaratorList();
          accept( TK::SCol ); // eat ';'
          break;

        case TK::Void:
        case TK::Char:
        case TK::Int:
        case TK::Struct:
          // declaration-list compound-statement
          parseDeclarationList();
          parseCompoundStatement();
          break;

        case TK::LBrace:
          parseCompoundStatement();
          break;

        default:
          {
            // If the first parsed init-declarator contains an assignment,
            // we would only expect comma ',' or semi-colon ';'.
            std::ostringstream actual;
            printTok( actual, current );

            errorf( current->pos, "expected %s before %s",
                "';', '{', ',' or type-specifier",
                actual.str().c_str() );
          }
      } // end switch
      break; // end declaration-specifiers

    default:
      {
        std::ostringstream actual;
        printTok( actual, current );

        errorf( current->pos, "expected %s before %s",
            "declaration or function-definition expected",
            actual.str().c_str() );
      }
  } // end switch
  return *( new IllegalStatement() );
} // end parseExternalDeclaration
