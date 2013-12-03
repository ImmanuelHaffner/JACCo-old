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


/// Binary Operator Precedences
///
/// \return the precedence of the binary operator 'tok', or -1 iff tok is not a
/// binary operator
static int getBinOpPrecedence( Lex::TK tk )
{
  switch ( tk )
  {
    case Lex::TK::Mul:
    case Lex::TK::Div:
    case Lex::TK::Mod:
      return 100;

    case Lex::TK::Plus:
    case Lex::TK::Minus:
      return 90;

    case Lex::TK::RShift:
    case Lex::TK::LShift:
      return 80;

    case Lex::TK::Le:
    case Lex::TK::Gr:
    case Lex::TK::LEq:
    case Lex::TK::GEq:
      return 70;

    case Lex::TK::Eq:
    case Lex::TK::NE:
      return 60;

    case Lex::TK::And:
      return 50;

    case Lex::TK::Xor:
      return 40;

    case Lex::TK::Or:
      return 30;

    case Lex::TK::LAnd:
      return 20;

    case Lex::TK::LOr:
      return 10;

      //
      //  IMPORTANT:
      //  Must never return 0.
      //

    default: return -1;
  }
} // end getBinOpPrecedence

int Parser::getTokenPrecedence()
{
  if ( ! this->current )
    return -1;

  int prec = getBinOpPrecedence( this->current->kind );
  return  prec > 0 ? prec : -1;
}

void Parser::readNextToken()
{
  if ( current ) delete current;
  current = next;
  next = new Lex::Token( lexer.getToken() );
}

static inline void errorpf( Pos pos, char const * const expected,
    char const * const actual )
{
  errorf( pos, "expected %s before %s", expected, actual );
}

#define ERROR( MSG ) \
  std::ostringstream actual; printTok( actual, current ); \
errorpf( current->pos, ( MSG ), actual.str().c_str() )

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
bool Parser::accept( Lex::TK tk )
{
  if ( ! is( tk ) )
  {
    std::ostringstream expected;
    printTK( expected, tk );

    std::ostringstream actual;
    printTok( actual, current );

    errorpf( current->pos, expected.str().c_str(), actual.str().c_str() );
    return false;
  }
  else
    readNextToken(); // eat token
  return true;
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

Expr const * Parser::parsePrimaryExpr()
{
  switch( current->kind )
  {
    case TK::IDENTIFIER:
      {
        Expr *expr = new Variable( *current );
        readNextToken(); // eat identifier
        return expr;
      }

    case TK::CONSTANT:
      {
        Expr *expr = new Constant( *current );
        readNextToken(); // eat constant
        return expr;
      }

    case TK::STRING_LITERAL:
      {
        Expr *expr = new StringLiteral( *current );
        readNextToken(); // eat string-literal
        return expr;
      }

    case TK::LPar:
      {
        readNextToken(); // eat '('
        Expr const * const expr = parseExpr();
        accept( TK::RPar ); // eat ')'
        return expr;
      }

    default:
      ERROR( "identifier, constant, string-literal or '(' expression ')'" );

  } // end switch
  return new IllegalExpr( *current );
} // end parsePrimaryExpr

Expr const * Parser::parsePostfixExpr()
{
  Expr const * expr = parsePrimaryExpr();

  for (;;)
  {
    switch ( current->kind )
    {
      case TK::LBracket:
        {
          Token const tok( *current );
          readNextToken(); // eat '['
          Expr const * const subscript = parseExpr();
          accept( TK::RBracket ); // eat ']'
          expr = new SubscriptExpr( tok, expr, subscript );
        }
        break;

      case TK::LPar:
        {
          Token const tok( *current );
          readNextToken(); // eat '('
          if ( current->kind != TK::RPar )
            // TODO add arg-expr-list
            parseArgumentExprList();
          accept( TK::RPar ); // eat ')'
          expr = new FunctionCall( tok, *expr );
        }
        break;

      case TK::PtrOp:
        {
          Token const  tok( *current );
          readNextToken(); // eat '->'
          Token const id( *current );
          if ( accept( TK::IDENTIFIER ) ) // eat Identifier
            expr = new ArrowExpr( tok, *expr, id );
          else
            expr = new IllegalExpr( id );
        }
        break;

      case TK::Dot:
        {
          Token const tok( *current );
          readNextToken(); // eat '.'
          Token const id( *current );
          if ( accept( TK::IDENTIFIER ) ) // eat Identifier
            expr = new DotExpr( tok, *expr, id );
          else
            expr = new IllegalExpr( id );
        }
        break;

      case TK::IncOp:
        expr = new PostIncExpr( *current, *expr );
        readNextToken(); // eat '++'
        break;

      case TK::DecOp:
        expr = new PostDecExpr( *current, *expr );
        readNextToken(); // eat '--'
        break;

      default: goto for_end; // exit loop
    } // end switch
  } // end for
for_end:
  return expr;
} // end parsePostfixExpr

Expr const * Parser::parseArgumentExprList()
{
  parseAssignmentExpr();
  while ( current->kind == TK::Comma )
    parseAssignmentExpr();
  return new IllegalExpr( *current );
} // end parseArgumentExprList

Expr const * Parser::parseUnaryExpr()
{
  switch ( current->kind )
  {
    case TK::IncOp:
      {
        Token const tok( *current );
        readNextToken(); // eat '++'
        return new PreIncExpr( tok, parseUnaryExpr() );
      }

    case TK::DecOp:
      {
        Token const tok( *current );
        readNextToken(); // eat '--'
        return new PreDecExpr( tok, parseUnaryExpr() );
      }

    case TK::Sizeof:
      {
        Token const tok( *current );
        readNextToken(); // eat 'sizeof'
        if ( current->kind == TK::LPar )
          switch ( next->kind )
          {
            case TK::Void:
            case TK::Char:
            case TK::Int:
            case TK::Struct:
              {
                readNextToken(); // eat '('
                Type const * const type = parseTypeName();
                accept( TK::RPar ); // eat ')'
                return new SizeofTypeExpr( tok, type );
              }

            default:;
          } // end switch
        return new SizeofExpr( tok, parseUnaryExpr() );
      }

    case Lex::TK::And:
    case Lex::TK::Mul:
    case Lex::TK::Plus:
    case Lex::TK::Minus:
    case Lex::TK::Neg:
    case Lex::TK::Not:
      {
        Token const tok( *current );
        readNextToken(); // eat unary operator
        // TODO
        parseCastExpr();
      }
      break;

    default:
      return parsePostfixExpr();
  } // end switch
  return new IllegalExpr( *current );
} // end parseUnaryExpr

Expr const * Parser::parseCastExpr()
{
  while ( current->kind == TK::LPar )
  {
    readNextToken(); // eat '('
    parseTypeName();
    accept( TK::RPar ); // eat ')'
  }
  parseUnaryExpr();
  return new IllegalExpr( *current );
} // end parseCastExpr

Expr const * Parser::parseBinaryExpr()
{
  Expr const * const lhs = parseCastExpr();
  return parseBinOpRHS( 0, lhs );
} // end parseBinaryExpr

Expr const * Parser::parseBinOpRHS( int exprPrec, Expr const * const lhs )
{
  int tokPrec = getTokenPrecedence();

  // If this binary expression binds less than lhs, we are done.
  if ( tokPrec < exprPrec )
    return lhs;

  Token const binOp( *current );
  readNextToken(); // eat BinOp

  Expr const * const rhs = parseCastExpr();

  // If binOp binds less with the RHS than the operator after RHS, let the
  // pending operator take RHS as its LHS.
  int nextPrec = getTokenPrecedence();
  if ( tokPrec < nextPrec )
    return new BinaryExpr( binOp, lhs,
          parseBinOpRHS( tokPrec + 1, rhs ) );

  return new BinaryExpr( binOp, lhs, rhs );
} // end parseBinOpRHS

Expr const * Parser::parseConditionalExpr()
{
  Expr const * const expr = parseBinaryExpr();

  if ( current->kind == TK::QMark )
  {
    Token const tok( *current );
    readNextToken(); // eat '?'
    Expr const * const lhs = parseExpr();
    accept( TK::Col ); // eat ':'
    return new ConditionalExpr( tok, expr, lhs, parseConditionalExpr() );
  }

  return expr;
} // end parseConditionalExpr

/// Note: we diverge from the ANSI-C grammar when parsing the
/// assignment-expression production. ANSI-C specifies that the LHS of an
/// assignment operator should be parsed as a unary-expression, but consistency
/// dictates that it be a conditional-expession. In practice, the important
/// thing here is that the LHS of an assignment has to be an l-value, which
/// productions between unary-expression and conditional-expression don't
/// produce. Because we want consistency, we parse the LHS as a
/// conditional-expression, then check for l-value-ness in semantic analysis
/// stages.
Expr const * Parser::parseAssignmentExpr()
{
  Expr const * const expr = parseConditionalExpr();

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
      {
        Token const tok( *current );
        readNextToken(); // eat assignment-operator
        return new AssignmentExpr( tok, expr, parseAssignmentExpr() );
      }

    default:;
  } // end switch

  return expr;
} // end parseAssignmentExpr

Expr const * Parser::parseExpr()
{
  // TODO
  parseAssignmentExpr();

  while ( current->kind == TK::Comma )
  {
    readNextToken(); // eat ','
    parseAssignmentExpr();
  }

  return new IllegalExpr( *current );
} // end parseExpr


//
//  Declarations
//

Decl const * Parser::parseDecl()
{
  parseTypeSpecifier();
  if ( current->kind != TK::SCol )
    parseDeclarator();
  accept( TK::SCol ); // eat ';'
  return new IllegalDecl( *current );
} // end parseDecl

TypeSpecifier const * Parser::parseTypeSpecifier()
{
  switch ( current->kind )
  {
    case TK::Void:
      readNextToken();
      return new TypeSpecifier( *current, NULL, NULL);
    case TK::Char:
      readNextToken();
      return new TypeSpecifier( *current, NULL, NULL );
    case TK::Int:
      readNextToken();
      return new TypeSpecifier( *current, NULL, NULL  ); 
    case TK::Struct:
      return parseStructSpecifier();

    default:
      {
        ERROR( "type-specifier ('void', 'char', 'int' or 'struct')" );
      }
  } // end switch
  return new IllegalTypeSpecifier( *current, NULL, NULL );
} // end parseTypeSpecifier

TypeSpecifier const * Parser::parseStructSpecifier()
{
  accept( TK::Struct );
  switch ( current->kind )
  {
    case TK::IDENTIFIER:
      readNextToken(); // eat identifier
      if ( current->kind == TK::LBrace )
      {
        readNextToken(); // eat '{'
        parseStructDeclList();
        accept( TK::RBrace ); // eat '}'
      }
      break;

    case TK::LBrace:
      readNextToken(); // eat '{'
      parseStructDeclList();
      accept( TK::RBrace ); // eat '}'
      break;

    default:
      {
        ERROR( "identifier or '{' struct-declaration-list '}'" );
      }
  } // end switch
  return new IllegalTypeSpecifier( *current, NULL, NULL );
} // end parseStructOrUnionSpecifier

Decl const * Parser::parseStructDeclList()
{
  do
  {
    parseStructDecl();
  }
  while ( current->kind != TK::RBrace );
  return new IllegalDecl( *current );
} // end parseStructDeclList

Decl const * Parser::parseStructDecl()
{
  parseTypeSpecifier();
  parseStructDeclaratorList();
  accept( TK::SCol ); // eat ';'
  return new IllegalDecl( *current );
} // end parseStructDecl

Decl const * Parser::parseStructDeclaratorList()
{
  parseDeclarator();
  while ( current->kind == TK::Comma )
  {
    readNextToken(); // eat ','
    parseDeclarator();
  }
  return new IllegalDecl( *current );
} // end parseStructDeclaratorList

Decl const * Parser::parseDeclarator()
{
  if ( current->kind == TK::Mul )
    parsePointer();
  parseDirectDeclarator();
  return new IllegalDecl( *current );
} // end parseDeclarator

Decl const * Parser::parseDirectDeclarator()
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
        ERROR( "identifier or '(' declarator ')'" );

  } // end switch

  while (current->kind == TK::LPar)
  {
    readNextToken(); // eat '('
    parseParameterList();
    accept( TK::RPar ); // eat ')'
  } // end while
  return new IllegalDecl( *current );
} // end parseDirectDeclarator

Decl const * Parser::parsePointer()
{
  accept( TK::Mul ); // '*'
  while ( current->kind == TK::Mul )
    readNextToken(); // eat '*'
  return new IllegalDecl( *current );
} // end parsePointer

Decl const * Parser::parseParameterList()
{
  parseParameterDecl();
  while ( current->kind == TK::Comma )
  {
    readNextToken(); // eat ','
    parseParameterDecl();
  }
  return new IllegalDecl( *current );
} // end parseParameterList

Decl const * Parser::parseParameterDecl()
{
  parseTypeSpecifier();
  switch ( current->kind )
  {
    case TK::IDENTIFIER:
      parseDeclarator();
      break;

    case TK::Mul:
    case TK::LPar:
      parseMaybeAbstractDeclarator();
      break;

    default:;
  }
  return new IllegalDecl( *current );
} // end parseParameterDecl

Type const * Parser::parseTypeName()
{
  //parseSpecifierQualifierList();

  switch ( current->kind )
  {
    case TK::Mul:
    case TK::LPar:
    case TK::LBracket:
      parseAbstractDeclarator();
      break;

    default:;
  }
  return new IllegalType( *current );
} // end parseTypeName

Decl const * Parser::parseAbstractDeclarator()
{
  switch ( current->kind )
  {
    case TK::Mul:
      parsePointer();
      switch ( current->kind )
      {
        case TK::LPar:
          parseDirectAbstractDeclarator();
          break;

        default:
          //return AbstractDeclarator;
          ;
      } // end switch
      break;

    case TK::LPar:
      parseDirectAbstractDeclarator();
      break;

    default:
      {
        ERROR( "'*' or direct-abstract-declarator" );
      }
  } // end switch
  return new IllegalDecl( *current );
} // end parseAbstractDeclarator

Decl const * Parser::parseDirectAbstractDeclarator()
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
          parseAbstractDeclarator();
          break;

        case TK::Void:
        case TK::Char:
        case TK::Int:
        case TK::Struct:
          parseParameterList();
          break;

        default:
          {
            ERROR( "abstract-declarator or parameter-type-list" );
          }
      } // end switch
      accept( TK::RPar ); // eat ')'
      break;

    default:
      {
        ERROR( "(abstract-declarator|parameter-type-list)" );
      }
  } // end switch

  while ( current->kind == TK::LPar )
  {
    readNextToken(); // eat '('
    if ( current->kind != TK::RPar )
      parseParameterList();
    accept( TK::RPar );

  } // end while
  return new IllegalDecl( *current );
} // end parseDirectAbstractDeclarator

Decl const * Parser::parseMaybeAbstractDeclarator()
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

        case TK::LPar:
          parseDirectMaybeAbstractDeclarator();
          break;

        default:;
      } // end switch
      break;

    case TK::IDENTIFIER:
      parseDirectDeclarator();
      break;

    case TK::LPar:
      parseDirectMaybeAbstractDeclarator();
      break;

    default:
      {
        ERROR( "'*', identifier, '(' [abstract-]declarator ')' or "
            "'(' parameter-type-list ')' "
            "expected" );
      }
  } // end switch

  return new IllegalDecl( *current );
} // end parseMaybeAbstractDeclarator

Decl const * Parser::parseDirectMaybeAbstractDeclarator()
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
      parseMaybeAbstractDeclarator();
      break;

    case TK::Void:
    case TK::Char:
    case TK::Int:
    case TK::Struct:
      parseParameterList();
      break;

    default:
      {
        ERROR( "identifier, '(' [abstract-]declarator ')' or  "
            "'(' parameter-list ')'" );
      }
  } // end switch
  return new IllegalDecl( *current );
} // end parseDirectMaybeAbstractDeclarator

Stmt const * Parser::parseStmt()
{
  switch ( current->kind )
  {
    case TK::IDENTIFIER:
      // labeled-statement or expression-statement
      if ( next->kind == TK::Col )
        parseLabeledStmt();
      else
        parseExprStmt();
      break;

    case TK::Case:
    case TK::Default:
      parseLabeledStmt();
      break;

    case TK::LBrace:
      parseCompoundStmt();
      break;

    case TK::If:
    case TK::Switch:
      parseSelectionStmt();
      break;

    case TK::For:
    case TK::While:
    case TK::Do:
      parseIterationStmt();
      break;

    case TK::Goto:
    case TK::Break:
    case TK::Continue:
    case TK::Return:
      parseJumpStmt();
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
      parseExprStmt();
      break;

    default:
      {
        ERROR( "statement" );
      }
  } // end switch
  return new IllegalStmt( *current );
} // end parseStmt

Stmt const * Parser::parseLabeledStmt()
{
  switch ( current->kind )
  {
    case TK::IDENTIFIER:
      readNextToken(); // eat identifier
      accept( TK::Col ); // eat ':'
      parseStmt();
      break;

    case TK::Case:
      readNextToken(); // eat 'case'
      parseConstantExpr();
      accept( TK::Col ); // eat ':'
      parseStmt();
      break;

    case TK::Default:
      readNextToken(); // eat 'default'
      accept( TK::Col ); // eat ':'
      parseStmt();
      break;

    default:
      {
        ERROR( "identifier, 'case' or 'default'" );
      }
  } // end switch
  return new IllegalStmt( *current );
} // end parseLabeledStmt

Stmt const * Parser::parseCompoundStmt()
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
      parseDeclList();
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
          parseStmt();
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
      parseStmtList();
      break;

    default:
      {
        ERROR( "declaration or statement" );
      }
  } // end switch
  accept( TK::RBrace ); // eat '}'
  return new IllegalStmt( *current );
} // end parseCompoundStmt

Stmt const * Parser::parseDeclList()
{
  parseDecl();

  for (;;)
  {
    switch ( current->kind )
    {
      case TK::Void:
      case TK::Char:
      case TK::Int:
      case TK::Struct:
        parseDecl();
        break;

      default: goto for_end;
    }
  } // end for
for_end:
  return new IllegalStmt( * current );
} // end parseDeclList

Stmt const * Parser::parseStmtList()
{
  parseStmt();

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
        parseStmt();
        break;

      default: goto for_end;
    }
  } // end for
for_end:
  return new IllegalStmt( *current );
} // end parseStmtList

Stmt const * Parser::parseExprStmt()
{
  if ( current->kind != TK::SCol )
    parseExpr();
  accept( TK::SCol );
  return new IllegalStmt( *current );
} // end parseExprStmt

Stmt const * Parser::parseSelectionStmt()
{
  switch ( current->kind )
  {
    case TK::If:
      readNextToken(); // eat 'if'
      accept( TK::LPar ); // eat '('
      parseExpr();
      accept( TK::RPar ); // eat ')'
      parseStmt();
      if ( current->kind == TK::Else )
      {
        readNextToken(); // eat 'else'
        parseStmt();
      }
      break;

    case TK::Switch:
      readNextToken(); // eat 'switch'
      accept( TK::LPar ); // eat '('
      parseExpr();
      accept( TK::RPar ); // eat ')'
      parseStmt();
      break;

    default:
      {
        ERROR( "'if' or 'switch'" );
      }
  } // end switch
  return new IllegalStmt( *current );
} // end parseSelectionStmt

Stmt const * Parser::parseIterationStmt()
{
  switch ( current->kind )
  {
    case TK::For:
      readNextToken(); // eat 'for'
      accept( TK::LPar ); // eat '('
      parseExprStmt(); // initialization
      parseExprStmt(); // condition
      if ( current->kind != TK::RPar )
        parseExpr(); // increment
      accept( TK::RPar ); // eat ')'
      parseStmt(); // body
      break;

    case TK::While:
      readNextToken(); // eat 'while'
      accept( TK::LPar ); // eat '('
      parseExpr(); // condition
      accept( TK::RPar ); // eat ')'
      parseStmt(); // body
      break;

    case TK::Do:
      readNextToken(); // eat 'do'
      parseStmt(); // body
      accept( TK::While ); // eat 'while'
      accept( TK::LPar ); // eat '('
      parseExpr(); // condition
      accept( TK::LPar ); // eat ')'
      break;

    default:
      {
        ERROR( "'for', 'do' or 'while'" );
      }
  } // end switch
  return new IllegalStmt( *current );
} // end parseIterationStmt

Stmt const * Parser::parseJumpStmt()
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
        parseExpr();
      accept( TK::SCol ); // eat ';'
      break;

    default:
      {
        ERROR( "'return', 'continue', 'break' or 'goto'" );
      }
  } // end switch
  return new IllegalStmt( *current );
} // end parseJumpStmt

Stmt const * Parser::parseTranslationUnit()
{
  do
  {
    // TODO stop or recover, if a corrupted external declaration was found
    Token const *prev = current;
    parseExternalDecl();
    if ( prev == current )
      readNextToken();
  }
  while ( current->kind != TK::END_OF_FILE );
  return new IllegalStmt( *current );
} // end parseTranslationUnit

Stmt const * Parser::parseExternalDecl()
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
          parseDeclList();
          break;

        default:;
      } // end switch
      parseCompoundStmt();
      break; // end declarator

    case TK::Void:
    case TK::Char:
    case TK::Int:
    case TK::Struct:
      // declaration-specifiers
      parseTypeSpecifier();
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
      parseDeclarator();

      switch ( current->kind )
      {
        case TK::SCol:
          // init-declarator-list
          readNextToken(); // eat ';'
          break;

        case TK::Comma:
          // init-declarator-list
          readNextToken(); // eat ','
          //parseInitDeclaratorList();
          accept( TK::SCol ); // eat ';'
          break;

        case TK::Void:
        case TK::Char:
        case TK::Int:
        case TK::Struct:
          // declaration-list compound-statement
          parseDeclList();
          parseCompoundStmt();
          break;

        case TK::LBrace:
          parseCompoundStmt();
          break;

        default:
          {
            // If the first parsed init-declarator contains an assignment,
            // we would only expect comma ',' or semi-colon ';'.
            ERROR( "';', '{', ',' or type-specifier" );
          }
      } // end switch
      break; // end declaration-specifiers

    default:
      {
        ERROR( "declaration or function-definition" );
      }
  } // end switch
  return new IllegalStmt( *current );
} // end parseExternalDecl
