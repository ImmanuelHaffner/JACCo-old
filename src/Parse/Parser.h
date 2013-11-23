//===--- Parser.h ---------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the Parser interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_PARSER_H
#define C4_PARSER_H

#include <iostream>
#include <sstream>
#include <unordered_map>
#include "../util.h"
#include "../diagnostic.h"
#include "../Lex/Token.h"
#include "../Lex/Lexer.h"
#include "../AST/AST.h"


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


// End First1

namespace C4
{

  //===----------------------------------------------------------------------===//
  //
  //  Operator Precedences
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
        //  0 not allowed as return value!!
        //

      default: return -1;
    }
  } // end getBinOpPrecedence
  
  static bool isUnaryOperator( Lex::TK tk )
  {
    switch ( tk )
    {
      case Lex::TK::And:
      case Lex::TK::Mul:
      case Lex::TK::Plus:
      case Lex::TK::Minus:
      case Lex::TK::Neg:
      case Lex::TK::Not:
        return true;

      default: return false;
    }
  }

  namespace Parse
  {
    /// \brief The parser.
    struct Parser
    {
      Parser( Lex::Lexer &lexer );
      ~Parser();

      /// Parses the tokens returned by the lexer, and construct the
      /// corresponding AST.
      void parse();


      private:
      Lex::Lexer &lexer;
      Lex::Token const * current;
      Lex::Token const * next;


      //===----------------------------------------------------------------===//
      //
      //  Parser Helper Functions
      //
      //===----------------------------------------------------------------===//

      /// This functions moves sets 'current' to 'next', and sets 'next' to the
      /// token returned from the lexer.
      /// This function offers a small, fixed-size token buffer.
      void getNextToken();

      /// Necessary for compatibility, use neutral element of LOr
      ///
      /// \return false
      inline bool is()
      {
        return false;
      }

      /// \return true, iff the token peeked by the lexer is of the specified
      /// TK
      inline bool is( Lex::TK tk )
      {
        return current->kind == tk;
      }

      /// \return true, iff the text of the token, peeked py the lexer, equals
      /// the specified string
      inline bool is( std::string const &s )
      {
        return is( s.c_str() );
      }

      /// \return true, iff the text of the token, peeked py the lexer, equals
      /// the specified string
      inline bool is( char const * const s )
      {
        return strEq( current->sym.str(), s );
      }

      /// \return true, iff the symbol of the current token equals the specified
      /// symbol.
      inline bool is( Symbol sym )
      {
        return current->sym == sym;
      }

      /// \return true, iff at least one of the specified arguments matches the
      /// token peeked by the lexer, i.e. if a call to is( ... ) for at least
      /// one argument yields true
      template < typename T, typename... Args >
        bool is( T t, Args... args );

      /// If the current token is "like" t, i.e. a call to is( t ) would return
      /// true, gets the next token, otherwise prints an error message.
      template < typename T >
        void accept( T t );

      int getTokenPrecedence()
      {
        if ( ! this->current )
          return -1;

        int prec = getBinOpPrecedence( this->current->kind );
        return  prec > 0 ? prec : -1;
      }


      //===----------------------------------------------------------------===//
      //
      //  Parser Sub Functions
      //
      //  These functions parse particular rules of the grammar, e.g.
      //  declarations or expressions.
      //
      //===----------------------------------------------------------------===//

      /// Parses an expression.
      ///
      /// \return the parsed expression
      AST::Expression & parseExpression();
      AST::Expression & parsePrimaryExpression();
      AST::Expression & parseUnaryExpression();
      AST::Expression & parseBinOpRHS( int exprPrec, AST::Expression &lhs );

    }; // end struct Parser

    //===------------------------------------------------------------------===//
    //
    //  Parser Helper Functions
    //
    //===------------------------------------------------------------------===//

    template < typename T, typename... Args >
      bool Parser::is( T t, Args... args )
      {
        return is( t ) || is( args... );
      }

    template < typename T >
      void Parser::accept( T t )
      {
        if ( ! is( t ) )
        {
          std::ostringstream oss;
          oss << "unexpected " << *current << ", expected " << t;
          errorf( current->pos, "%s", oss.str().c_str() );
        }
        else
          getNextToken();
      }
  } // end namespace Parse
} // end namespace C4

#endif
