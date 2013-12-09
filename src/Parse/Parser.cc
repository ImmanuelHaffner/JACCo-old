//===--- Parser.cc --------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements the Parser interface.
//
//===----------------------------------------------------------------------===//

#include "Parser.h"
#include <vector>

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


//===----------------------------------------------------------------------===//
//
//  Parser Helper Functions
//
//===----------------------------------------------------------------------===//

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
{ std::ostringstream actual; printTok( actual, current ); \
errorpf( current->pos, ( MSG ), actual.str().c_str() ); }

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
  this->root = parseTranslationUnit();
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
          Expr const * args = NULL;
          if ( current->kind != TK::RPar )
            args = parseArgumentExprList();
          accept( TK::RPar ); // eat ')'
          expr = new FunctionCall( tok, expr, args );
        }
        break;

      case TK::PtrOp:
        {
          Token const  tok( *current );
          readNextToken(); // eat '->'
          Token const id( *current );
          if ( accept( TK::IDENTIFIER ) ) // eat Identifier
            expr = new ArrowExpr( tok, expr, id );
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
            expr = new DotExpr( tok, expr, id );
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
  ExprList * const args = new ExprList( *current );
  args->append( parseAssignmentExpr() );
  while ( current->kind == TK::Comma )
  {
    readNextToken(); // eat ','
    args->append( parseAssignmentExpr() );
  }
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
                // SIZEOF '(' type_name ')'
                readNextToken(); // eat '('
                Type const * const type = parseTypeName();
                accept( TK::RPar ); // eat ')'
                return new SizeofTypeExpr( tok, type );
              }

            default:; // SIZEOF '(' expr ')'
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
        return new UnaryOperation( tok, parseUnaryExpr() );
      }

    default:;
  } // end switch
  return parsePostfixExpr();
} // end parseUnaryExpr

Expr const * Parser::parseBinaryExpr()
{
  Expr const * const lhs = parseUnaryExpr();
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

  Expr const * const rhs = parseUnaryExpr();

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
  ExprList * const exprList = new ExprList( *current );
  exprList->append( parseAssignmentExpr() );

  while ( current->kind == TK::Comma )
  {
    readNextToken(); // eat ','
    exprList->append( parseAssignmentExpr() );
  }

  return new IllegalExpr( *current );
} // end parseExpr

Expr const * Parser::parseConstantExpr()
{
  return parseConditionalExpr();
} // end parseConstantExpr


//
//  Declarations
//

Decl const * Parser::parseDecl()
{
  TypeSpecifier const * const typeSpec = parseTypeSpecifier();
  Declarator const * declarator = NULL;
  if ( current->kind != TK::SCol )
    declarator = parseDeclarator();
  accept( TK::SCol ); // eat ';'
  return new Decl( typeSpec, declarator );
} // end parseDecl

TypeSpecifier const * Parser::parseTypeSpecifier()
{
  switch ( current->kind )
  {
    case TK::Void:
    case TK::Char:
    case TK::Int:
      {
        Token tok( *current );
        readNextToken(); // eat type
        return new TypeSpecifier( tok );
      }

    case TK::Struct:
      return parseStructSpecifier();

    default:
      ERROR( "type-specifier ('void', 'char', 'int' or 'struct')" );

  } // end switch
  return new IllegalTypeSpecifier( *current );
} // end parseTypeSpecifier

TypeSpecifier const * Parser::parseStructSpecifier()
{
  Token const tok( *current );
  if ( accept( TK::Struct ) ) // eat 'struct'
    switch ( current->kind )
    {
      case TK::IDENTIFIER:
        {
          Token const id( *current );
          readNextToken(); // eat identifier
          if ( current->kind == TK::LBrace )
          {
            readNextToken(); // eat '{'
            StructDeclList const * const structDecls = parseStructDeclList();
            accept( TK::RBrace ); // eat '}'
            return new StructSpecifier( tok, &id, structDecls );
          }
          return new StructSpecifier( tok, &id );
        }

      case TK::LBrace:
        {
          readNextToken(); // eat '{'
          StructDeclList const * const structDecls = parseStructDeclList();
          accept( TK::RBrace ); // eat '}'
          return new StructSpecifier( tok, structDecls );
        }

      default:
        ERROR( "identifier or '{' struct-declaration-list '}'" );

    } // end switch
  return new IllegalTypeSpecifier( *current );
} // end parseStructOrUnionSpecifier

StructDeclList const * Parser::parseStructDeclList()
{
  StructDeclList const * const structDecls = new StructDeclList();
  do
  {
    parseStructDecl();
  }
  while ( current->kind != TK::RBrace ); // until '}'
  return structDecls;
} // end parseStructDeclList

StructDecl const * Parser::parseStructDecl()
{
  TypeSpecifier const * const typeSpec = parseTypeSpecifier();
  StructDeclaratorList const * const structDeclarators = parseStructDeclaratorList();
  accept( TK::SCol ); // eat ';'
  return new StructDecl( typeSpec, structDeclarators );
} // end parseStructDecl

StructDeclaratorList const * Parser::parseStructDeclaratorList()
{
  StructDeclaratorList const * const structDeclarators =
    new StructDeclaratorList();

  parseDeclarator();
  while ( current->kind == TK::Comma )
  {
    readNextToken(); // eat ','
    parseDeclarator();
  }
  return structDeclarators;
} // end parseStructDeclaratorList

Declarator const * Parser::parseDeclarator( DeclaratorType const dt )
{
  size_t pointerCount = 0;
  if ( current->kind == TK::Mul )
    pointerCount = parsePointer();

  Declarator const * decl = NULL;
  if ( dt == DeclaratorType::NORMAL ||  // a direct declarator MUST follow
      current->kind == TK::LPar )       // a direct declarator MIGHT follow
    decl = parseDirectDeclarator( dt );

  if ( ( pointerCount == 0 || dt == DeclaratorType::NORMAL ) &&  ! decl )
  {
    ERROR( "pointer or declarator" );
    return new IllegalDeclarator( *current );
  }

  if ( pointerCount == 0 )
    return decl;

  return new Pointer( *current, pointerCount, decl );
} // end parseDeclarator

size_t Parser::parsePointer()
{
  size_t pointerCount = 0;
  if ( accept( TK::Mul ) ) // eat '*'
    ++pointerCount;

  while ( current->kind == TK::Mul )
  {
    readNextToken(); // eat '*'
    pointerCount++;
  }
  return pointerCount;
} // end parsePointer

Declarator const * Parser::parseDirectDeclarator( DeclaratorType const dt )
{
  Declarator const * decl = NULL;
  ParamList const * paramList = NULL;
  switch ( current->kind )
  {
    case TK::LPar:
      readNextToken(); // eat '('
      if ( dt == DeclaratorType::NORMAL )
        decl = parseDeclarator( dt );
      else
      {
        switch ( current->kind )
        {
          case TK::RPar:
            break;

          case TK::Void:
          case TK::Char:
          case TK::Int:
          case TK::Struct:
            paramList = parseParameterList();
            // Abstract Function Declarator
            return new FunctionDeclarator( *current, NULL, paramList );

          case TK::Mul:
          case TK::LPar:
            decl = parseDeclarator( dt );
            break;

          default:
            ERROR( "declarator or parameter-list" );
        } // end switch
      }
      accept( TK::RPar ); // eat ')'
      break;

    case TK::IDENTIFIER:
      if ( dt == DeclaratorType::NORMAL )
      {
        decl = new Identifier( *current );
        readNextToken(); // eat identifier
        break;
      }
      // no break here; run into default

    default:
      ERROR( "identifier, '(' declarator ')' or '( [parameter-list] ')'" );
  } // end switch

  // read parameter-list suffix
  while ( current->kind == TK::LPar )
  {
    readNextToken(); // eat '('
    switch ( current->kind )
    {
      case TK::RPar:
        break;

      case TK::Void:
      case TK::Char:
      case TK::Int:
      case TK::Struct:
        paramList = parseParameterList();

      default:
        paramList = new ParamList();
    }
    accept( TK::RPar ); // eat ')'
  }
  
  if ( paramList )
    return new FunctionDeclarator( *current, decl, paramList );
  
  return decl; 
} // end parseDirectDeclarator

ParamList const * Parser::parseParameterList()
{
  ParamList * const params = new ParamList();
  params->append( parseParameterDecl() );
  while ( current->kind == TK::Comma )
  {
    readNextToken(); // eat ','
    params->append( parseParameterDecl() );
  }
  return params;
} // end parseParameterList

ParamDecl const * Parser::parseParameterDecl()
{
  TypeSpecifier const * const typeSpec = parseTypeSpecifier();
  switch ( current->kind )
  {
    case TK::IDENTIFIER:
      return new ParamDecl( typeSpec, parseDeclarator() );

    case TK::Mul:
    case TK::LPar:
      return new ParamDecl( typeSpec,
          parseDeclarator( DeclaratorType::UNKNOWN ) );

    default:;
  }
  return new ParamDecl( typeSpec );
} // end parseParameterDecl

Type const * Parser::parseTypeName()
{
  parseTypeSpecifier();

  switch ( current->kind )
  {
    case TK::Mul:
    case TK::LPar:
      parseDeclarator( DeclaratorType::ABSTRACT);
      break;

    default:;
  }
  return new IllegalType( *current );
} // end parseTypeName

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
      ERROR( "statement" );

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

CompoundStmt const * Parser::parseCompoundStmt()
{
  CompoundStmt * const compStmt = new CompoundStmt( *current );

  accept( TK::LBrace ); // eat '{'

  for (;;)
  {
    switch ( current->kind )
    {
      case TK::RBrace:
        goto for_end;

      case TK::Comma:
        readNextToken(); // eat ','
        break;

      case TK::Void:
      case TK::Char:
      case TK::Int:
      case TK::Struct:
        compStmt->append( new BlockItem( parseDecl() ) );
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
        compStmt->append( new BlockItem( parseStmt() ) );
        break;

      default:
        ERROR( "declaration or statement" );
        goto for_end;

    } // end switch
  } // end for

for_end:
  accept( TK::RBrace ); // eat '}'
  return compStmt;
} // end parseCompoundStmt

DeclList const * Parser::parseDeclList()
{
  DeclList * const declList = new DeclList();
  declList->append( parseDecl() );
  for (;;)
  {
    switch ( current->kind )
    {
      case TK::Void:
      case TK::Char:
      case TK::Int:
      case TK::Struct:
        declList->append( parseDecl() );
        break;

      default: goto for_end;
    }
  } // end for
for_end:
  return declList;
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

TranslationUnit const * Parser::parseTranslationUnit()
{
  TranslationUnit * unit = new TranslationUnit();
  do
  {
    // TODO stop or recover, if a corrupted external declaration was found
    Token const *prev = current;
    unit->append( parseExtDecl() );
    if ( prev == current )
      readNextToken();
  }
  while ( current->kind != TK::END_OF_FILE );
  return unit;
} // end parseTranslationUnit

FunctionDef const * Parser::parseFunctionDef(
    TypeSpecifier const * const typeSpecifier,
    Declarator const * const declarator )
{
  DeclList const * decls = NULL;
  switch ( current->kind )
  {
    case TK::LBrace:
      break;

    case TK::Void:
    case TK::Char:
    case TK::Int:
    case TK::Struct:
      decls = parseDeclList();
      break;

    default:
        ERROR( "declaration" );
        return NULL;

  } // end switch

  return new FunctionDef( typeSpecifier, declarator, decls,
      parseCompoundStmt() );
} // end parseFunctionDefinition

ExtDecl const * Parser::parseExtDecl()
{
  switch ( current->kind )
  {
    // type_specifier
    case TK::Void:
    case TK::Char:
    case TK::Int:
    case TK::Struct:
      {
        TypeSpecifier const * const typeSpec = parseTypeSpecifier();
        if ( current->kind == TK::SCol )
        {
          readNextToken(); // eat ';'
          return new Decl( typeSpec );
        }
        Declarator const * const declarator = parseDeclarator();
        switch ( current->kind )
        {
          case TK::SCol:
            readNextToken(); // eat ';'
            return new Decl( typeSpec, declarator );

          case TK::Void:
          case TK::Char:
          case TK::Int:
          case TK::Struct:
          case TK::LBrace:
            return parseFunctionDef( typeSpec, declarator );

          default:
            ERROR( "';' or function-definition" );
        } // end switch
        return new IllegalDecl( *current, typeSpec );
      }

    // declarator
    case TK::IDENTIFIER:
    case TK::Mul:
    case TK::LPar:
      {
        Declarator const * const declarator = parseDeclarator();
        return parseFunctionDef( NULL, declarator );
      }

    default:
      ERROR( "function-definition or declaration" );
  } // end switch
  return new IllegalExtDecl( *current );
} // end parseExtDecl
