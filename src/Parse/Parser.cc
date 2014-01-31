//===--- Parser.cc --------------------------------------------------------===//
//
//  ~~~ The C4 Compiler ~~~
//
//  This file implements the Parser interface.
//
//===----------------------------------------------------------------------===//

#include "Parser.h"
#include <vector>

using namespace C4;
using namespace Parse;
using namespace Lex;
using namespace AST;


static bool functionDeclarator = false;


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


TranslationUnit const * Parser::parse()
{
  readNextToken();
  readNextToken();
  assert( current && "must not be NULL" );
  assert( next && "must not be NULL" );
  return parseTranslationUnit();
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
        Expr const * const expr = factory.getVariable( *current );
        readNextToken(); // eat identifier
        return expr;
      }

    case TK::CONSTANT:
      {
        Expr const * const expr = factory.getConstant( *current );
        readNextToken(); // eat constant
        return expr;
      }

    case TK::STRING_LITERAL:
      {
        Expr const * const expr = factory.getStringLiteral( *current );
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
  return factory.getIllegalExpr( *current );
} // end parsePrimaryExpr

Expr const * Parser::parsePostfixExpr()
{
  Expr const * expr = parsePrimaryExpr();

  for (;;)
  {
    switch ( current->kind )
    {
      case TK::LBracket: // array subscript
        {
          Token const tok( *current );
          readNextToken(); // eat '['
          Expr const * const subscript = parseExpr();
          accept( TK::RBracket ); // eat ']'
          expr = factory.getSubscriptExpr( tok, expr, subscript );
        }
        break;

      case TK::LPar: // function call
        {
          Token const tok( *current );
          readNextToken(); // eat '('
          Expr const * args = NULL;
          if ( current->kind != TK::RPar )
            args = parseArgumentExprList();
          accept( TK::RPar ); // eat ')'
          expr = factory.getFunctionCall( tok, expr, args );
        }
        break;

      case TK::PtrOp:
        {
          Token const  tok( *current );
          readNextToken(); // eat '->'
          Token const id( *current );
          if ( accept( TK::IDENTIFIER ) ) // eat Identifier
            expr = factory.getArrowExpr( tok, expr, id );
          else
            expr = factory.getIllegalExpr( tok );
        }
        break;

      case TK::Dot:
        {
          Token const tok( *current );
          readNextToken(); // eat '.'
          Token const id( *current );
          if ( accept( TK::IDENTIFIER ) ) // eat Identifier
            expr = factory.getDotExpr( tok, expr, id );
          else
            expr = factory.getIllegalExpr( *current );
        }
        break;

      case TK::IncOp:
        expr = factory.getPostIncExpr( *current, expr );
        readNextToken(); // eat '++'
        break;

      case TK::DecOp:
        expr = factory.getPostDecExpr( *current, expr );
        readNextToken(); // eat '--'
        break;

      default: goto for_end; // exit loop
    } // end switch
  } // end for
for_end:
  return expr;
} // end parsePostfixExpr

ExprList const * Parser::parseArgumentExprList()
{
  std::vector< Expr const * > exprs;
  Token const tok(*current);

  exprs.push_back( parseAssignmentExpr() );
  while ( current->kind == TK::Comma )
  {
    readNextToken(); // eat ','
    exprs.push_back( parseAssignmentExpr() );
  }
  return factory.getExprList( tok, exprs );
} // end parseArgumentExprList

Expr const * Parser::parseUnaryExpr()
{
  switch ( current->kind )
  {
    case TK::IncOp:
      {
        Token const tok( *current );
        readNextToken(); // eat '++'
        return factory.getPreIncExpr( tok, parseUnaryExpr() );
      }

    case TK::DecOp:
      {
        Token const tok( *current );
        readNextToken(); // eat '--'
        return factory.getPreDecExpr( tok, parseUnaryExpr() );
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
                TypeName const * const type = parseTypeName();
                accept( TK::RPar ); // eat ')'
                return factory.getSizeofTypeExpr( tok, type );
              }

            default:; // SIZEOF '(' expr ')'
          } // end switch
        return factory.getSizeofExpr( tok, parseUnaryExpr() );
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
        return factory.getUnaryOperation( tok, parseUnaryExpr() );
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

Expr const * Parser::parseBinOpRHS( int exprPrec, Expr const * lhs )
{
  for (;;)
  {
    int tokPrec = getTokenPrecedence();

    // If this binary expression binds less than lhs, we are done.
    if ( tokPrec < exprPrec )
      return lhs;

    Token const binOp( *current );
    readNextToken(); // eat BinOp

    Expr const * rhs = parseUnaryExpr();

    // If binOp binds less with the RHS than the operator after RHS, let the
    // pending operator take RHS as its LHS.
    int nextPrec = getTokenPrecedence();
    if ( tokPrec < nextPrec )
      rhs = parseBinOpRHS( tokPrec + 1, rhs );

    lhs = factory.getBinaryExpr( binOp, lhs, rhs );
  } // end for
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
    return factory.getConditionalExpr( tok, expr, lhs, parseConditionalExpr() );
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
        return factory.getAssignmentExpr( tok, expr, parseAssignmentExpr() );
      }

    default:;
  } // end switch

  return expr;
} // end parseAssignmentExpr

Expr const * Parser::parseExpr()
{
  Token const tok(*current);
  Expr const * const expr = parseAssignmentExpr();
  if ( current->kind != TK::Comma )
    return expr;

  std::vector< Expr const * > exprs;
  exprs.push_back( expr );

  while ( current->kind == TK::Comma )
  {
    readNextToken(); // eat ','
    exprs.push_back( parseAssignmentExpr() );
  }

  return factory.getExprList( tok, exprs );
} // end parseExpr


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
  return factory.getDecl( typeSpec, declarator );
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
        return factory.getTypeSpecifier( tok );
      }

    case TK::Struct:
      return parseStructSpecifier();

    default:
      ERROR( "type-specifier ('void', 'char', 'int' or 'struct')" );

  } // end switch
  return factory.getIllegalTypeSpecifier( *current );
} // end parseTypeSpecifier

TypeSpecifier const * Parser::parseStructSpecifier()
{
  Token const tok( *current );
  accept( TK::Struct ); // eat 'struct'
  switch ( current->kind )
  {
    case TK::IDENTIFIER:
      {
        Token const * const id = new Token(*current);
        readNextToken(); // eat identifier
        if ( current->kind == TK::LBrace )
        {
          readNextToken(); // eat '{'
          StructDeclList const * const structDecls = parseStructDeclList();
          accept( TK::RBrace ); // eat '}'
          return factory.getStructSpecifier( tok, id, structDecls );
        }
        return factory.getStructSpecifier( tok, id );
      }

    case TK::LBrace:
      {
        readNextToken(); // eat '{'
        StructDeclList const * const structDecls = parseStructDeclList();
        accept( TK::RBrace ); // eat '}'
        return factory.getStructSpecifier( tok, structDecls );
      }

    default:
      ERROR( "identifier or '{' struct-declaration-list '}'" );

  } // end switch
  return factory.getIllegalTypeSpecifier( *current );
} // end parseStructOrUnionSpecifier

StructDeclList const * Parser::parseStructDeclList()
{
  std::vector< StructDecl const * > structDecls;
  do
    structDecls.push_back( parseStructDecl() );
  while ( current->kind != TK::END_OF_FILE &&
      current->kind != TK::RBrace ); // until EOF or '}'
  return factory.getStructDeclList( structDecls );
} // end parseStructDeclList

StructDecl const * Parser::parseStructDecl()
{
  TypeSpecifier const * const typeSpec = parseTypeSpecifier();
  StructDeclaratorList const * structDeclarators = NULL;
  if ( current->kind != TK::SCol )
    structDeclarators = parseStructDeclaratorList();
  accept( TK::SCol ); // eat ';'
  return factory.getStructDecl( typeSpec, structDeclarators );
} // end parseStructDecl

StructDeclaratorList const * Parser::parseStructDeclaratorList()
{
  std::vector< Declarator const * > structDeclarators;

  structDeclarators.push_back( parseDeclarator() );
  while ( current->kind == TK::Comma )
  {
    readNextToken(); // eat ','
    structDeclarators.push_back( parseDeclarator() );
  }
  return factory.getStructDeclaratorList( structDeclarators );
} // end parseStructDeclaratorList

PointerDeclarator const * Parser::parsePointerDeclarator(
    DeclaratorType const dt /*= NORMAL*/ )
{
  Token const tok( *current );
  Declarator const * subDeclarator = NULL;

  readNextToken(); // eat *
  if ( dt == DeclaratorType::NORMAL )
    subDeclarator = parseDeclarator();
  else
    switch ( current->kind )
    {
      case TK::IDENTIFIER:
      case TK::LPar:
        subDeclarator = parseDeclarator( dt );
        break;

      default:;
    } // end switch

  return factory.getPointerDeclarator( tok, subDeclarator );
} // end parsePointerDeclarator

Declarator const * Parser::parseDeclarator(
    DeclaratorType const dt /*= NORMAL*/ )
{
  Token const tok( *current );
  Declarator const * declarator = NULL;
  ParamList const * paramList = NULL;

  switch ( current->kind )
  {
    case TK::LPar:
      readNextToken(); // eat '('
      if ( dt == DeclaratorType::NORMAL )
        declarator = parseDeclarator( dt );
      else
      {
        switch ( current->kind )
        {
          /* Empty parameter list: '(' ')'
           */
          case TK::RPar:
            paramList = new ParamList();
            break;

          /* Non-empty parameter list.
           */
          case TK::Void:
          case TK::Char:
          case TK::Int:
          case TK::Struct:
            paramList = parseParameterList();
            break;

          case TK::Mul:
            declarator = parsePointerDeclarator( dt );
            break;

          /* Nested parenthesis.
           */
          case TK::LPar:
            declarator = parseDeclarator( dt );
            break;

          default:
            ERROR( "declarator or parameter-list" );
        } // end switch
      }
      accept( TK::RPar ); // eat ')'
      break;

    case TK::Mul:
      declarator = parsePointerDeclarator( dt );
      break;

    case TK::IDENTIFIER:
      if ( dt != DeclaratorType::ABSTRACT )
      {
        readNextToken(); // eat identifier
        declarator = factory.getIdentifier( tok );
        break;
      }
      // no break here; run into default

    default:
      switch ( dt )
      {
        case DeclaratorType::NORMAL:
          ERROR( "identifier or '(' declarator ')'" );
          break;

        case DeclaratorType::ABSTRACT:
          ERROR( "'(' declarator ')' or '(' [parameter-list] ')'" );
          break;

        default:
          ERROR( "identifier, '(' declarator ')' or '(' [parameter-list] ')'" );
      } // end switch
  } // end switch

  /* Read parameter-list suffix, if it exists and we did not already parse a
   * parameter list.
   */
  if ( ! paramList && current->kind == TK::LPar )
  {
    readNextToken(); // eat '('
    switch ( current->kind )
    {
      case TK::RPar:
        paramList = new ParamList();
        break;

      case TK::Void:
      case TK::Char:
      case TK::Int:
      case TK::Struct:
        paramList = parseParameterList();
        break;

      default:
        ERROR( "parameter-list" );

    } // end switch
    accept( TK::RPar ); // eat ')'
  }

  if ( paramList )
  {
    functionDeclarator = true;
    return factory.getFunctionDeclarator( tok, declarator, paramList );
  }
  if ( declarator ) return declarator;
  return factory.getIllegalDeclarator( *current );
} // end parseDeclarator

ParamList const * Parser::parseParameterList()
{
  std::vector< ParamDecl const * > paramDecls;

  paramDecls.push_back( parseParameterDecl() );
  while ( current->kind == TK::Comma )
  {
    readNextToken(); // eat ','
    paramDecls.push_back( parseParameterDecl() );
  }
  return factory.getParamList( paramDecls );
} // end parseParameterList

ParamDecl const * Parser::parseParameterDecl()
{
  TypeSpecifier const * const typeSpec = parseTypeSpecifier();
  switch ( current->kind )
  {
    case TK::IDENTIFIER:
      return factory.getParamDecl( typeSpec, parseDeclarator() );

    case TK::Mul:
    case TK::LPar:
      return factory.getParamDecl( typeSpec,
          parseDeclarator( DeclaratorType::UNKNOWN ) );

    default:;
  }
  return factory.getParamDecl( typeSpec );
} // end parseParameterDecl

TypeName const * Parser::parseTypeName()
{
  Token const tok( *current );
  TypeSpecifier const * const typeSpec = parseTypeSpecifier();
  Declarator const * declarator = NULL;
  switch ( current->kind )
  {
    case TK::Mul:
    case TK::LPar:
      declarator = parseDeclarator( DeclaratorType::ABSTRACT );
      break;

    default:;
  }
  return factory.getTypeName( tok, typeSpec, declarator );
} // end parseTypeName

Stmt const * Parser::parseStmt()
{
  switch ( current->kind )
  {
    case TK::IDENTIFIER:
      // labeled-statement or expression-statement
      if ( next->kind == TK::Col )
        return parseLabeledStmt();
      else
        return parseExprStmt();
      break;

    case TK::Case:
    case TK::Default:
      return parseLabeledStmt();
      break;

    case TK::LBrace:
      return parseCompoundStmt();
      break;

    case TK::If:
    case TK::Switch:
      return parseSelectionStmt();
      break;

    case TK::For:
    case TK::While:
    case TK::Do:
      return parseIterationStmt();
      break;

    case TK::Goto:
    case TK::Break:
    case TK::Continue:
    case TK::Return:
      return parseJumpStmt();
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
      return parseExprStmt();
      break;

    default:
      ERROR( "statement" );

  } // end switch
  return factory.getIllegalStmt( *current );
} // end parseStmt

Stmt const * Parser::parseLabeledStmt()
{
  Token const tok( *current );
  switch ( current->kind )
  {
    case TK::IDENTIFIER:
      readNextToken(); // eat identifier
      accept( TK::Col ); // eat ':'
      break;

    case TK::Case:
      {
        readNextToken(); // eat 'case'
        Expr const * const expr = parseConditionalExpr();
        accept( TK::Col ); // eat ':'
        return factory.getCaseStmt( tok, expr, parseStmt() );
      }

    case TK::Default:
      readNextToken(); // eat 'default'
      accept( TK::Col ); // eat ':'
      break;

    default:
      {
        ERROR( "identifier, 'case' or 'default'" );
        return factory.getIllegalStmt( *current );
      }
  } // end switch
  return factory.getLabelStmt( tok, parseStmt() );
} // end parseLabeledStmt

CompoundStmt const * Parser::parseCompoundStmt()
{
  env.pushScope();
  Token const tok(*current);
  std::vector< BlockItem const * > items;

  accept( TK::LBrace ); // eat '{'

  for (;;)
  {
    switch ( current->kind )
    {
      case TK::RBrace:
        goto for_end;

      /*case TK::Comma:
        readNextToken(); // eat ','
        break;*/

      case TK::Void:
      case TK::Char:
      case TK::Int:
      case TK::Struct:
        items.push_back( factory.getBlockItem( parseDecl() ) );
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
        items.push_back( factory.getBlockItem( parseStmt() ) );
        break;

      default:
        ERROR( "declaration or statement" );
        goto for_end;

    } // end switch
  } // end for

for_end:
  accept( TK::RBrace ); // eat '}'
  env.popScope();
  return factory.getCompoundStmt( tok, items );
} // end parseCompoundStmt

DeclList const * Parser::parseDeclList()
{
  std::vector< Decl const * > decls;

  decls.push_back( parseDecl() );
  for (;;)
  {
    switch ( current->kind )
    {
      case TK::Void:
      case TK::Char:
      case TK::Int:
      case TK::Struct:
        decls.push_back( parseDecl() );
        break;

      default: goto for_end;
    }
  } // end for
for_end:
  return factory.getDeclList( decls );
} // end parseDeclList

ExprStmt const * Parser::parseExprStmt()
{
  Token const tok( *current );
  Expr const * expr = NULL;
  if ( current->kind != TK::SCol )
    expr = parseExpr();
  accept( TK::SCol ); // eat ';'
  return factory.getExprStmt( tok, expr );
} // end parseExprStmt

Stmt const * Parser::parseSelectionStmt()
{
  Token const tok( *current );
  switch ( current->kind )
  {
    case TK::If:
      {
        readNextToken(); // eat 'if'
        accept( TK::LPar ); // eat '('
        Expr const * const cond = parseExpr();
        accept( TK::RPar ); // eat ')'
        Stmt const * const thenStmt = parseStmt();
        Stmt const * elseStmt = NULL;
        if ( current->kind == TK::Else )
        {
          readNextToken(); // eat 'else'
          elseStmt = parseStmt();
        }
        return factory.getIfStmt( tok, cond, thenStmt, elseStmt );
      }

    case TK::Switch:
      {
        readNextToken(); // eat 'switch'
        accept( TK::LPar ); // eat '('
        Expr const * const cond = parseExpr();
        accept( TK::RPar ); // eat ')'
        Stmt const * const body = parseStmt();
        return factory.getSwitchStmt( tok, cond, body );
      }

    default:
      {
        ERROR( "'if' or 'switch'" );
      }
  } // end switch
  return factory.getIllegalStmt( *current );
} // end parseSelectionStmt

Stmt const * Parser::parseIterationStmt()
{
  Token const tok( *current );
  switch ( current->kind )
  {
    case TK::For:
      {
        readNextToken(); // eat 'for'
        accept( TK::LPar ); // eat '('

        Expr const * init = NULL;
        Decl const * initDecl = NULL;
        switch ( current->kind )
        {
          case TK::SCol:
            break;

          case TK::Void:
          case TK::Char:
          case TK::Int:
          case TK::Struct:
            initDecl = parseDecl(); // init declaration
            break;

          default:
            init = parseExpr(); // initialization
        } // end switch
        accept( TK::SCol ); // eat ';'

        Expr const * cond = NULL;
        if ( current->kind != TK::SCol )
          cond = parseExpr(); // condition
        accept( TK::SCol ); // eat ';'

        Expr const * step = NULL;
        if ( current->kind != TK::RPar )
          step = parseExpr(); // increment

        accept( TK::RPar ); // eat ')'
        Stmt const * const body = parseStmt(); // body
        if ( init )
          return factory.getForStmt( tok, init, cond, step, body );
        return factory.getForStmt( tok, initDecl, cond, step, body );
      }

    case TK::While:
      {
        readNextToken(); // eat 'while'
        accept( TK::LPar ); // eat '('
        Expr const * cond = parseExpr(); // condition
        accept( TK::RPar ); // eat ')'
        Stmt const * body = parseStmt(); // body
        return factory.getWhileStmt( tok, cond, body );
      }

    case TK::Do:
      {
        readNextToken(); // eat 'do'
        Stmt const * const body = parseStmt(); // body
        accept( TK::While ); // eat 'while'
        accept( TK::LPar ); // eat '('
        Expr const * const cond = parseExpr(); // condition
        accept( TK::RPar ); // eat ')'
        accept( TK::SCol ); // eat ';'
        return factory.getDoStmt( tok, body, cond );
      }

    default:
      ERROR( "'for', 'do' or 'while'" );

  } // end switch
  return factory.getIllegalStmt( *current );
} // end parseIterationStmt

Stmt const * Parser::parseJumpStmt()
{
  Token const tok( *current );
  switch ( current->kind )
  {
    case TK::Goto:
      {
        readNextToken(); // eat 'goto'
        Token const id( *current );
        bool b = accept( TK::IDENTIFIER ); // eat identifier
        accept( TK::SCol ); // eat ';'
        if ( b )
          return factory.getGotoStmt( id );
      }
      break;

    case TK::Continue:
      readNextToken(); // eat 'continue'
      accept( TK::SCol ); // eat ';'
      return factory.getContinueStmt( tok );

    case TK::Break:
      readNextToken(); // eat 'break'
      accept( TK::SCol ); // eat ';'
      return factory.getBreakStmt( tok );

    case TK::Return:
      {
        Expr const * expr = NULL;
        readNextToken(); // eat 'return'
        if ( current->kind != TK::SCol )
          expr = parseExpr();
        accept( TK::SCol ); // eat ';'
        return factory.getReturnStmt( tok, expr );
      }

    default:
      ERROR( "'return', 'continue', 'break' or 'goto'" );

  } // end switch
  return factory.getIllegalStmt( *current );
} // end parseJumpStmt

TranslationUnit const * Parser::parseTranslationUnit()
{
  std::vector< ExtDecl const * > extDecls;

  do
  {
    Pos const old( current->pos );
    extDecls.push_back( parseExtDecl() ); // in bad cases, does not consume any token

    // If the parseExtDecl function did not consume anything, consume one token,
    // to avoid divergance of the parser.
    //if ( old == current->pos )
    //readNextToken();

    // Recover until the end of a block (e.g compound statement) or semicolon
    // ';'
    if ( old == current->pos )
    {
      for (;;)
      {
        switch ( current->kind )
        {
          case TK::END_OF_FILE:
            goto for_end;

          case TK::SCol:
          case TK::RBrace:
            readNextToken();
            goto for_end;

          default:
            readNextToken();
        } // end switch
      } // end for

for_end:
      continue;
    }
  }
  while ( current->kind != TK::END_OF_FILE );
  return factory.getTranslationUnit( extDecls );
} // end parseTranslationUnit

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

        // check whether we have a struct decl, and the decl ends here
        if ( typeSpec->tok.kind == TK::Struct &&
            ( current->kind == TK::END_OF_FILE || current->kind == TK::SCol ) )
        {
          accept( TK::SCol ); // eat ';'
          return factory.getDecl( typeSpec );
        }

        functionDeclarator = false;
        Declarator const * const declarator = parseDeclarator();
        switch ( current->kind )
        {
          case TK::SCol:
            readNextToken(); // eat ';'
            return factory.getDecl( typeSpec, declarator );

          case TK::LBrace:
            if ( ! functionDeclarator )
              ERROR( "'(' [parameter-list] ')'" );
            return factory.getFunctionDef( typeSpec, declarator,
                parseCompoundStmt() );

          default:
            ERROR( "';' or function-definition" );
        } // end switch
        return factory.getIllegalDecl( *current, typeSpec );
      }

    default:
      ERROR( "function-definition or declaration" );
  } // end switch
  return factory.getIllegalExtDecl( *current );
} // end parseExtDecl
