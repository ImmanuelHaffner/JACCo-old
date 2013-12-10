//===--- Parser.cc --------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements the Parser interface.
//
//===----------------------------------------------------------------------===//

#include "Parser.h"


//===----------------------------------------------------------------------===//
//
//  First1
//
//===----------------------------------------------------------------------===//

#define PARAMETER_LIST \
  "auto", \
  "char", \
  "const", \
  "enum", \
  "extern", \
  "int", \
  "long", \
  "register", \
  "short", \
  "signed", \
  "static", \
  "struct", \
  "typedef", \
  "type_name", \
  "unsigned", \
  "void", \
  "volatile"

#define TYPE_SPECIFIER \
  "char", \
  "enum", \
  "int", \
  "long", \
  "short", \
  "signed", \
  "struct", \
  "type_name", \
  "unsigned", \
  "void"

#define POSTFIX_EXPRESSION \
  "(", \
  Lex::TK::CONSTANT, \
  Lex::TK::IDENTIFIER, \
  Lex::TK::STRING_LITERAL

#define FUNCTION_DEFINITION \
  "(", \
  "*", \
  "auto", \
  "char", \
  "const", \
  "enum", \
  "extern", \
  Lex::TK::IDENTIFIER, \
  "int", \
  "long", \
  "register", \
  "short", \
  "signed", \
  "static", \
  "struct", \
  "typedef", \
  "type_name", \
  "unsigned", \
  "void", \
  "volatile"

#define DECLARATOR \
  "(", \
  "*", \
  Lex::TK::IDENTIFIER

#define STATEMENT \
  "!", \
  "&", \
  "(", \
  "*", \
  "+", \
  "-", \
  ";", \
  "{", \
  "~", \
  "break", \
  "case", \
  Lex::TK::CONSTANT, \
  "continue", \
  "dec_op", \
  "default", \
  "do", \
  "for", \
  "goto", \
  Lex::TK::IDENTIFIER, \
  "if", \
  "inc_op", \
  "return", \
  "sizeof", \
  Lex::TK::STRING_LITERAL, \
  "switch", \
  "while"

#define UNARY_OPERATOR \
  "!", \
  "&", \
  "*", \
  "+", \
  "-", \
  "~"

#define STRUCT_DECLARATOR_LIST \
  "(", \
  "*", \
  ":", \
  Lex::TK::IDENTIFIER

#define ASSIGNMENT_EXPRESSION \
  "!", \
  "&", \
  "(", \
  "*", \
  "+", \
  "-", \
  "~", \
  Lex::TK::CONSTANT, \
  "dec_op", \
  Lex::TK::IDENTIFIER, \
  "inc_op", \
  "sizeof", \
  Lex::TK::STRING_LITERAL

#define INIT_DECLARATOR \
  "(", \
  "*", \
  Lex::TK::IDENTIFIER

#define ENUMERATOR \
  Lex::TK::IDENTIFIER

#define LABELED_STATEMENT \
  "case", \
  "default", \
  Lex::TK::IDENTIFIER

#define LOGICAL_OR_EXPRESSION \
  "!", \
  "&", \
  "(", \
  "*", \
  "+", \
  "-", \
  "~", \
  Lex::TK::CONSTANT, \
  "dec_op", \
  Lex::TK::IDENTIFIER, \
  "inc_op", \
  "sizeof", \
  Lex::TK::STRING_LITERAL

#define PARAMETER_TYPE_LIST \
  "auto", \
  "char", \
  "const", \
  "enum", \
  "extern", \
  "int", \
  "long", \
  "register", \
  "short", \
  "signed", \
  "static", \
  "struct", \
  "typedef", \
  "type_name", \
  "unsigned", \
  "void", \
  "volatile"

#define STATEMENT_LIST \
  "!", \
  "&", \
  "(", \
  "*", \
  "+", \
  "-", \
  ";", \
  "{", \
  "~", \
  "break", \
  "case", \
  Lex::TK::CONSTANT, \
  "continue", \
  "dec_op", \
  "default", \
  "do", \
  "for", \
  "goto", \
  Lex::TK::IDENTIFIER, \
  "if", \
  "inc_op", \
  "return", \
  "sizeof", \
  Lex::TK::STRING_LITERAL, \
  "switch", \
  "while"

#define STRUCT_DECLARATOR \
  "(", \
  "*", \
  ":", \
  Lex::TK::IDENTIFIER

#define POINTER \
  "*"

#define INCLUSIVE_OR_EXPRESSION \
  "!", \
  "&", \
  "(", \
  "*", \
  "+", \
  "-", \
  "~", \
  Lex::TK::CONSTANT, \
  "dec_op", \
  Lex::TK::IDENTIFIER, \
  "inc_op", \
  "sizeof", \
  Lex::TK::STRING_LITERAL

#define EXPRESSION_STATEMENT \
  "!", \
  "&", \
  "(", \
  "*", \
  "+", \
  "-", \
  ";", \
  "~", \
  Lex::TK::CONSTANT, \
  "dec_op", \
  Lex::TK::IDENTIFIER, \
  "inc_op", \
  "sizeof", \
  Lex::TK::STRING_LITERAL

#define ENUMERATOR_LIST \
  Lex::TK::IDENTIFIER

#define TYPE_QUALIFIER \
  "const", \
  "volatile"

#define ENUM_SPECIFIER \
  "enum"

#define ARGUMENT_EXPRESSION_LIST \
  "!", \
  "&", \
  "(", \
  "*", \
  "+", \
  "-", \
  "~", \
  Lex::TK::CONSTANT, \
  "dec_op", \
  Lex::TK::IDENTIFIER, \
  "inc_op", \
  "sizeof", \
  Lex::TK::STRING_LITERAL

#define UNARY_EXPRESSION \
  "!", \
  "&", \
  "(", \
  "*", \
  "+", \
  "-", \
  "~", \
  Lex::TK::CONSTANT, \
  "dec_op", \
  Lex::TK::IDENTIFIER, \
  "inc_op", \
  "sizeof", \
  Lex::TK::STRING_LITERAL

#define IDENTIFIER_LIST \
  Lex::TK::IDENTIFIER

#define TYPE_NAME \
  "char", \
  "const", \
  "enum", \
  "int", \
  "long", \
  "short", \
  "signed", \
  "struct", \
  "type_name", \
  "unsigned", \
  "void", \
  "volatile"

#define LOGICAL_AND_EXPRESSION \
  "!", \
  "&", \
  "(", \
  "*", \
  "+", \
  "-", \
  "~", \
  Lex::TK::CONSTANT, \
  "dec_op", \
  Lex::TK::IDENTIFIER, \
  "inc_op", \
  "sizeof", \
  Lex::TK::STRING_LITERAL

#define DIRECT_DECLARATOR \
  "(", \
  Lex::TK::IDENTIFIER

#define STRUCT_DECLARATION \
  "char", \
  "const", \
  "enum", \
  "int", \
  "long", \
  "short", \
  "signed", \
  "struct", \
  "type_name", \
  "unsigned", \
  "void", \
  "volatile"

#define ADDITIVE_EXPRESSION \
  "!", \
  "&", \
  "(", \
  "*", \
  "+", \
  "-", \
  "~", \
  Lex::TK::CONSTANT, \
  "dec_op", \
  Lex::TK::IDENTIFIER, \
  "inc_op", \
  "sizeof", \
  Lex::TK::STRING_LITERAL

#define DECLARATION_SPECIFIERS \
  "auto", \
  "char", \
  "const", \
  "enum", \
  "extern", \
  "int", \
  "long", \
  "register", \
  "short", \
  "signed", \
  "static", \
  "struct", \
  "typedef", \
  "type_name", \
  "unsigned", \
  "void", \
  "volatile"

#define MULTIPLICATIVE_EXPRESSION \
  "!", \
  "&", \
  "(", \
  "*", \
  "+", \
  "-", \
  "~", \
  Lex::TK::CONSTANT, \
  "dec_op", \
  Lex::TK::IDENTIFIER, \
  "inc_op", \
  "sizeof", \
  Lex::TK::STRING_LITERAL

#define AND_EXPRESSION \
  "!", \
  "&", \
  "(", \
  "*", \
  "+", \
  "-", \
  "~", \
  Lex::TK::CONSTANT, \
  "dec_op", \
  Lex::TK::IDENTIFIER, \
  "inc_op", \
  "sizeof", \
  Lex::TK::STRING_LITERAL

#define EXTERNAL_DECLARATION \
  "(", \
  "*", \
  "auto", \
  "char", \
  "const", \
  "enum", \
  "extern", \
  Lex::TK::IDENTIFIER, \
  "int", \
  "long", \
  "register", \
  "short", \
  "signed", \
  "static", \
  "struct", \
  "typedef", \
  "type_name", \
  "unsigned", \
  "void", \
  "volatile"

#define INIT_DECLARATOR_LIST \
  "(", \
  "*", \
  Lex::TK::IDENTIFIER

#define CONSTANT_EXPRESSION \
  "!", \
  "&", \
  "(", \
  "*", \
  "+", \
  "-", \
  "~", \
  Lex::TK::CONSTANT, \
  "dec_op", \
  Lex::TK::IDENTIFIER, \
  "inc_op", \
  "sizeof", \
  Lex::TK::STRING_LITERAL

#define ASSIGNMENT_OPERATOR \
  "=", \
  "add_assign", \
  "and_assign", \
  "div_assign", \
  "left_assign", \
  "mod_assign", \
  "mul_assign", \
  "or_assign", \
  "right_assign", \
  "sub_assign", \
  "xor_assign"

#define TYPE_QUALIFIER_LIST \
  "const", \
  "volatile"

#define STRUCT_OR_UNION_SPECIFIER \
  "struct"

#define DIRECT_ABSTRACT_DECLARATOR \
  "(", \
  "["

#define SHIFT_EXPRESSION \
  "!", \
  "&", \
  "(", \
  "*", \
  "+", \
  "-", \
  "~", \
  Lex::TK::CONSTANT, \
  "dec_op", \
  Lex::TK::IDENTIFIER, \
  "inc_op", \
  "sizeof", \
  Lex::TK::STRING_LITERAL

#define DECLARATION \
  "auto", \
  "char", \
  "const", \
  "enum", \
  "extern", \
  "int", \
  "long", \
  "register", \
  "short", \
  "signed", \
  "static", \
  "struct", \
  "typedef", \
  "type_name", \
  "unsigned", \
  "void", \
  "volatile"

#define STRUCT_DECLARATION_LIST \
  "char", \
  "const", \
  "enum", \
  "int", \
  "long", \
  "short", \
  "signed", \
  "struct", \
  "type_name", \
  "unsigned", \
  "void", \
  "volatile"

#define INITIALIZER_LIST \
  "!", \
  "&", \
  "(", \
  "*", \
  "+", \
  "-", \
  "{", \
  "~", \
  Lex::TK::CONSTANT, \
  "dec_op", \
  Lex::TK::IDENTIFIER, \
  "inc_op", \
  "sizeof", \
  Lex::TK::STRING_LITERAL

#define JUMP_STATEMENT \
  "break", \
  "continue", \
  "goto", \
  "return"

#define RELATIONAL_EXPRESSION \
  "!", \
  "&", \
  "(", \
  "*", \
  "+", \
  "-", \
  "~", \
  Lex::TK::CONSTANT, \
  "dec_op", \
  Lex::TK::IDENTIFIER, \
  "inc_op", \
  "sizeof", \
  Lex::TK::STRING_LITERAL

#define COMPOUND_STATEMENT \
  "{"

#define TRANSLATION_UNIT \
  "(", \
  "*", \
  "auto", \
  "char", \
  "const", \
  "enum", \
  "extern", \
  Lex::TK::IDENTIFIER, \
  "int", \
  "long", \
  "register", \
  "short", \
  "signed", \
  "static", \
  "struct", \
  "typedef", \
  "type_name", \
  "unsigned", \
  "void", \
  "volatile"

#define PARAMETER_DECLARATION \
  "auto", \
  "char", \
  "const", \
  "enum", \
  "extern", \
  "int", \
  "long", \
  "register", \
  "short", \
  "signed", \
  "static", \
  "struct", \
  "typedef", \
  "type_name", \
  "unsigned", \
  "void", \
  "volatile"

#define STRUCT_OR_UNION \
  "struct"

#define STORAGE_CLASS_SPECIFIER \
  "auto", \
  "extern", \
  "register", \
  "static", \
  "typedef"

#define EXPRESSION \
  "!", \
  "&", \
  "(", \
  "*", \
  "+", \
  "-", \
  "~", \
  Lex::TK::CONSTANT, \
  "dec_op", \
  Lex::TK::IDENTIFIER, \
  "inc_op", \
  "sizeof", \
  Lex::TK::STRING_LITERAL

#define ABSTRACT_DECLARATOR \
  "(", \
  "*", \
  "["

#define EXCLUSIVE_OR_EXPRESSION \
  "!", \
  "&", \
  "(", \
  "*", \
  "+", \
  "-", \
  "~", \
  Lex::TK::CONSTANT, \
  "dec_op", \
  Lex::TK::IDENTIFIER, \
  "inc_op", \
  "sizeof", \
  Lex::TK::STRING_LITERAL

#define INITIALIZER \
  "!", \
  "&", \
  "(", \
  "*", \
  "+", \
  "-", \
  "{", \
  "~", \
  Lex::TK::CONSTANT, \
  "dec_op", \
  Lex::TK::IDENTIFIER, \
  "inc_op", \
  "sizeof", \
  Lex::TK::STRING_LITERAL

#define ITERATION_STATEMENT \
  "do", \
  "for", \
  "while"

#define DECLARATION_LIST \
  "auto", \
  "char", \
  "const", \
  "enum", \
  "extern", \
  "int", \
  "long", \
  "register", \
  "short", \
  "signed", \
  "static", \
  "struct", \
  "typedef", \
  "type_name", \
  "unsigned", \
  "void", \
  "volatile"

#define CAST_EXPRESSION \
  "!", \
  "&", \
  "(", \
  "*", \
  "+", \
  "-", \
  "~", \
  Lex::TK::CONSTANT, \
  "dec_op", \
  Lex::TK::IDENTIFIER, \
  "inc_op", \
  "sizeof", \
  Lex::TK::STRING_LITERAL

#define SPECIFIER_QUALIFIER_LIST \
  "char", \
  "const", \
  "enum", \
  "int", \
  "long", \
  "short", \
  "signed", \
  "struct", \
  "type_name", \
  "unsigned", \
  "void", \
  "volatile"

#define PRIMARY_EXPRESSION \
  "(", \
  Lex::TK::CONSTANT, \
  Lex::TK::IDENTIFIER, \
  Lex::TK::STRING_LITERAL

#define EQUALITY_EXPRESSION \
  "!", \
  "&", \
  "(", \
  "*", \
  "+", \
  "-", \
  "~", \
  Lex::TK::CONSTANT, \
  "dec_op", \
  Lex::TK::IDENTIFIER, \
  "inc_op", \
  "sizeof", \
  Lex::TK::STRING_LITERAL

#define CONDITIONAL_EXPRESSION \
  "!", \
  "&", \
  "(", \
  "*", \
  "+", \
  "-", \
  "~", \
  Lex::TK::CONSTANT, \
  "dec_op", \
  Lex::TK::IDENTIFIER, \
  "inc_op", \
  "sizeof", \
  Lex::TK::STRING_LITERAL

#define SELECTION_STATEMENT \
  "if", \
  "switch"

//
// End First1
//


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
      expr = new Variable( *current ); getNextToken(); break;

    case TK::CONSTANT:
      expr = new Constant( *current ); getNextToken(); break;

    case TK::STRING_LITERAL:
      expr = new StringLiteral( *current ); getNextToken(); break;

    case TK::LPar:
      {
        getNextToken(); // eat '('
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
      case TK::LBracket: // array subscript
        {
          getNextToken(); // eat '['
          parseExpression();
          accept( TK::RBracket ); // eat ']'
          break;
        }

      case TK::LPar: // function call
        {
          getNextToken(); // eat '('
          if ( current->kind != TK::RPar )
            parseArgumentExpressionList();
          accept( TK::RPar ); // eat ')'
          break;
        }

      case TK::PtrOp:
      case TK::Dot:
        {
          getNextToken(); // eat operator
          accept( TK::IDENTIFIER ); // eat Identifier
          break;
        }

      case TK::IncOp:
      case TK::DecOp:
        {
          getNextToken(); // eat operator
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
}

Expression & Parser::parseUnaryExpression()
{
  switch ( current->kind )
  {
    case TK::IncOp:
    case TK::DecOp:
      {
        getNextToken(); // eat operator
        parseUnaryExpression();
        break;
      }

    case TK::Sizeof:
      {
        getNextToken(); // eat 'sizeof'
        if ( next->kind == TK::LPar )
        {
          getNextToken(); // eat '('
          // TODO parse type-name
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
        getNextToken(); // eat unary operator
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
    getNextToken(); // eat '('
    // TODO parse type-name
    accept( TK::RPar ); // eat ')'
  }
  parseUnaryExpression();
  return *( new IllegalExpression() );
} // end parseCastExpression

Expression & Parser::parseBinaryExpression()
{
  Expression &lhs = parseUnaryExpression();
  return parseBinOpRHS( 0, lhs );
} // end parseBinaryExpression

Expression & Parser::parseBinOpRHS( int exprPrec, AST::Expression &lhs )
{
  int tokPrec = getTokenPrecedence();

  // If this binary expression binds less than lhs, we are done.
  if ( tokPrec < exprPrec )
    return lhs;

  Token const * binOp = this->current;
  getNextToken(); // eat BinOp

  Expression &rhs = parseUnaryExpression();

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
    getNextToken(); // eat '?'
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
        getNextToken(); // eat assignment-operator
        parseConditionalExpression();

      default:
        goto for_end2;
    }
  }
for_end2:
  return *( new IllegalExpression() );
} // end parseAssignmentExpression

Expression & Parser::parseExpression()
{
  parseAssignmentExpression();

  while ( current->kind == TK::Comma )
  {
    getNextToken(); // eat ','
    parseAssignmentExpression();
  }

  return *( new IllegalExpression() );
} // end parseExpression


//
//  Declarations
//

AST::Declaration & Parser::parseDeclaration()
{
  // TODO parse declaration-specifiers
  if ( current->kind != TK::SCol )
  {}
    // TODO parse init-declarator-list
  accept( TK::SCol ); // eat ';'
  return *( new IllegalDeclaration() );
}
