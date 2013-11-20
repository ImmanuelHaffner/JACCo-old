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
#include "../diagnostic.h"
#include "../Lex/Token.h"
#include "../Lex/Lexer.h"
#include "../AST/AST.h"
#include "../AST/Identifier.h"
#include "../AST/Constant.h"
#include "../AST/StringLiteral.h"


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
  Lex::TokenKind::CONSTANT, \
  Lex::TokenKind::IDENTIFIER, \
  Lex::TokenKind::STRING_LITERAL

#define FUNCTION_DEFINITION \
  "(", \
  "*", \
  "auto", \
  "char", \
  "const", \
  "enum", \
  "extern", \
  Lex::TokenKind::IDENTIFIER, \
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
  Lex::TokenKind::IDENTIFIER

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
  Lex::TokenKind::CONSTANT, \
  "continue", \
  "dec_op", \
  "default", \
  "do", \
  "for", \
  "goto", \
  Lex::TokenKind::IDENTIFIER, \
  "if", \
  "inc_op", \
  "return", \
  "sizeof", \
  Lex::TokenKind::STRING_LITERAL, \
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
  Lex::TokenKind::IDENTIFIER

#define ASSIGNMENT_EXPRESSION \
  "!", \
  "&", \
  "(", \
  "*", \
  "+", \
  "-", \
  "~", \
  Lex::TokenKind::CONSTANT, \
  "dec_op", \
  Lex::TokenKind::IDENTIFIER, \
  "inc_op", \
  "sizeof", \
  Lex::TokenKind::STRING_LITERAL

#define INIT_DECLARATOR \
  "(", \
  "*", \
  Lex::TokenKind::IDENTIFIER

#define ENUMERATOR \
  Lex::TokenKind::IDENTIFIER

#define LABELED_STATEMENT \
  "case", \
  "default", \
  Lex::TokenKind::IDENTIFIER

#define LOGICAL_OR_EXPRESSION \
  "!", \
  "&", \
  "(", \
  "*", \
  "+", \
  "-", \
  "~", \
  Lex::TokenKind::CONSTANT, \
  "dec_op", \
  Lex::TokenKind::IDENTIFIER, \
  "inc_op", \
  "sizeof", \
  Lex::TokenKind::STRING_LITERAL

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
  Lex::TokenKind::CONSTANT, \
  "continue", \
  "dec_op", \
  "default", \
  "do", \
  "for", \
  "goto", \
  Lex::TokenKind::IDENTIFIER, \
  "if", \
  "inc_op", \
  "return", \
  "sizeof", \
  Lex::TokenKind::STRING_LITERAL, \
  "switch", \
  "while"

#define STRUCT_DECLARATOR \
  "(", \
  "*", \
  ":", \
  Lex::TokenKind::IDENTIFIER

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
  Lex::TokenKind::CONSTANT, \
  "dec_op", \
  Lex::TokenKind::IDENTIFIER, \
  "inc_op", \
  "sizeof", \
  Lex::TokenKind::STRING_LITERAL

#define EXPRESSION_STATEMENT \
  "!", \
  "&", \
  "(", \
  "*", \
  "+", \
  "-", \
  ";", \
  "~", \
  Lex::TokenKind::CONSTANT, \
  "dec_op", \
  Lex::TokenKind::IDENTIFIER, \
  "inc_op", \
  "sizeof", \
  Lex::TokenKind::STRING_LITERAL

#define ENUMERATOR_LIST \
  Lex::TokenKind::IDENTIFIER

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
  Lex::TokenKind::CONSTANT, \
  "dec_op", \
  Lex::TokenKind::IDENTIFIER, \
  "inc_op", \
  "sizeof", \
  Lex::TokenKind::STRING_LITERAL

#define UNARY_EXPRESSION \
  "!", \
  "&", \
  "(", \
  "*", \
  "+", \
  "-", \
  "~", \
  Lex::TokenKind::CONSTANT, \
  "dec_op", \
  Lex::TokenKind::IDENTIFIER, \
  "inc_op", \
  "sizeof", \
  Lex::TokenKind::STRING_LITERAL

#define IDENTIFIER_LIST \
  Lex::TokenKind::IDENTIFIER

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
  Lex::TokenKind::CONSTANT, \
  "dec_op", \
  Lex::TokenKind::IDENTIFIER, \
  "inc_op", \
  "sizeof", \
  Lex::TokenKind::STRING_LITERAL

#define DIRECT_DECLARATOR \
  "(", \
  Lex::TokenKind::IDENTIFIER

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
  Lex::TokenKind::CONSTANT, \
  "dec_op", \
  Lex::TokenKind::IDENTIFIER, \
  "inc_op", \
  "sizeof", \
  Lex::TokenKind::STRING_LITERAL

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
  Lex::TokenKind::CONSTANT, \
  "dec_op", \
  Lex::TokenKind::IDENTIFIER, \
  "inc_op", \
  "sizeof", \
  Lex::TokenKind::STRING_LITERAL

#define AND_EXPRESSION \
  "!", \
  "&", \
  "(", \
  "*", \
  "+", \
  "-", \
  "~", \
  Lex::TokenKind::CONSTANT, \
  "dec_op", \
  Lex::TokenKind::IDENTIFIER, \
  "inc_op", \
  "sizeof", \
  Lex::TokenKind::STRING_LITERAL

#define EXTERNAL_DECLARATION \
  "(", \
  "*", \
  "auto", \
  "char", \
  "const", \
  "enum", \
  "extern", \
  Lex::TokenKind::IDENTIFIER, \
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
  Lex::TokenKind::IDENTIFIER

#define CONSTANT_EXPRESSION \
  "!", \
  "&", \
  "(", \
  "*", \
  "+", \
  "-", \
  "~", \
  Lex::TokenKind::CONSTANT, \
  "dec_op", \
  Lex::TokenKind::IDENTIFIER, \
  "inc_op", \
  "sizeof", \
  Lex::TokenKind::STRING_LITERAL

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
  Lex::TokenKind::CONSTANT, \
  "dec_op", \
  Lex::TokenKind::IDENTIFIER, \
  "inc_op", \
  "sizeof", \
  Lex::TokenKind::STRING_LITERAL

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
  Lex::TokenKind::CONSTANT, \
  "dec_op", \
  Lex::TokenKind::IDENTIFIER, \
  "inc_op", \
  "sizeof", \
  Lex::TokenKind::STRING_LITERAL

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
  Lex::TokenKind::CONSTANT, \
  "dec_op", \
  Lex::TokenKind::IDENTIFIER, \
  "inc_op", \
  "sizeof", \
  Lex::TokenKind::STRING_LITERAL

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
  Lex::TokenKind::IDENTIFIER, \
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
  Lex::TokenKind::CONSTANT, \
  "dec_op", \
  Lex::TokenKind::IDENTIFIER, \
  "inc_op", \
  "sizeof", \
  Lex::TokenKind::STRING_LITERAL

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
  Lex::TokenKind::CONSTANT, \
  "dec_op", \
  Lex::TokenKind::IDENTIFIER, \
  "inc_op", \
  "sizeof", \
  Lex::TokenKind::STRING_LITERAL

#define INITIALIZER \
  "!", \
  "&", \
  "(", \
  "*", \
  "+", \
  "-", \
  "{", \
  "~", \
  Lex::TokenKind::CONSTANT, \
  "dec_op", \
  Lex::TokenKind::IDENTIFIER, \
  "inc_op", \
  "sizeof", \
  Lex::TokenKind::STRING_LITERAL

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
  Lex::TokenKind::CONSTANT, \
  "dec_op", \
  Lex::TokenKind::IDENTIFIER, \
  "inc_op", \
  "sizeof", \
  Lex::TokenKind::STRING_LITERAL

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
  Lex::TokenKind::CONSTANT, \
  Lex::TokenKind::IDENTIFIER, \
  Lex::TokenKind::STRING_LITERAL

#define EQUALITY_EXPRESSION \
  "!", \
  "&", \
  "(", \
  "*", \
  "+", \
  "-", \
  "~", \
  Lex::TokenKind::CONSTANT, \
  "dec_op", \
  Lex::TokenKind::IDENTIFIER, \
  "inc_op", \
  "sizeof", \
  Lex::TokenKind::STRING_LITERAL

#define CONDITIONAL_EXPRESSION \
  "!", \
  "&", \
  "(", \
  "*", \
  "+", \
  "-", \
  "~", \
  Lex::TokenKind::CONSTANT, \
  "dec_op", \
  Lex::TokenKind::IDENTIFIER, \
  "inc_op", \
  "sizeof", \
  Lex::TokenKind::STRING_LITERAL

#define SELECTION_STATEMENT \
  "if", \
  "switch"


// End First1


//===----------------------------------------------------------------------===//
//
//  Operator Precedences
//
//===----------------------------------------------------------------------===//


// End Operator Precedences

namespace C4
{
  namespace Parse
  {
    struct Parser
    {
      Parser( Lex::Lexer &lexer );
      ~Parser();

      /*
       *
       * Parser Helper Functions
       *
       */

      /// Necessary for compatibility, does nothing.
      void pout( std::ostream &out )
      {
        out.rdbuf();
      }

      /// Prints t to the ostream out.
      inline void pout( std::ostream &out, Lex::TokenKind t )
      {
        out << t;
      }

      /// Prints t to the ostream out.
      template < typename T >
        void pout( std::ostream &out, T t )
        {
          out << "'" << t << "'";
        }

      /// Prints all arguments in the specified order to the ostream out.
      template < typename T, typename... Args >
        void pout( std::ostream &out, T t, Args... args )
        {
          pout( out, t );
          out << ", ";
          pout( out, args... );
        }

      /// Necessary for compatibility, use neutral element of LOr
      ///
      /// \return false
      inline bool is()
      {
        return false;
      }

      /// \return true, iff the token peeked by the lexer is of the specified
      /// TokenKind
      inline bool is( Lex::TokenKind tKind )
      {
        return lexer.getToken().kind == tKind;
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
        return lexer.getToken().sym.str() == s;
      }

      /// \return true, iff at least one of the specified arguments matches the
      /// token peeked by the lexer, i.e. if a call to is( ... ) for at least
      /// one argument yields true
      template < typename T, typename... Args >
        bool is( T t, Args... args )
        {
          return is( t ) || is( args... );
        }

      template < typename... Args >
        void err( Args... args )
        {
          Lex::Token &tok = lexer.getToken();

          switch ( tok.kind )
          {
            case Lex::TokenKind::ILLEGAL:
              {
                std::ostringstream oss;
                oss << tok.pos << " " << tok;
                errorf( tok.pos, "%s", oss.str().c_str() );
              }

            case Lex::TokenKind::END_OF_FILE:
              {
                std::ostringstream oss;
                oss << "unexpected end-of-file, expected one of: ";
                pout( oss, args... );
                errorf( tok.pos, "%s", oss.str().c_str() );
              }

            default:
              {
                std::ostringstream oss;
                oss << "unexpected '" << tok.sym << "', expected one of: ";
                pout( oss, args... );
                errorf( tok.pos, "%s", oss.str().c_str() );
              }
          }
        }

      /// Necessary for compatibility when using no follow-sets.
      void until() {}

      /// Gets tokens from the lexer, until a call to is( ... ) returns true.
      /// This function is used to read tokens, until a token in a follow set is
      /// found.
      template < typename... Args >
        void until( Args... args )
        {
          while ( ! is( args... ) )
            lexer.getToken();
        }

      /// Checks whether the token peeked by the lexer matches the first
      /// argument, by invoking match( ... ). If the token matches, gets the
      /// token from the lexer, else, invokes until( ... ) with the given follow
      /// set.
      template < typename T, typename... Args >
        void accept( T t, Args... args )
        {
          if ( is( t ) )
            lexer.getToken();
          else
            until( args... );
        }

      /// Parses the tokens returned by the lexer, and construct the
      /// corresponding AST.
      ///
      /// NOTE: This function may prompt errors/warnings to the console.
      inline void parse()
      {

      }

      /*
       *
       * Parser Sub Functions
       *
       */

      template < typename... Args >
      void parsePrimaryExpression( Args... args )
      {
        is( args... ); // TODO remove
      }

      template < typename... Args >
      void parsePostfixExpression( Args... args )
      {
        is( args... ); // TODO remove
      }

      template < typename... Args >
      void parseArgumentExpressionList( Args... args )
      {
        is( args... ); // TODO remove
      }

      template < typename... Args >
      void parseUnaryExpression( Args... args )
      {
        is( args... ); // TODO remove
      }
 
      template < typename... Args >
      void parseCastExpression( Args... args )
      {
        is( args... ); // TODO remove
      }

      template < typename... Args >
      void parseAssignmentOperator( Args... args )
      {
        is( args... ); // TODO remove
      }

      template < typename... Args >
      void parseExpression( Args... args )
      {
        is( args... ); // TODO remove
      }

      template < typename... Args >
      void parseStorageClassSpecifier( Args... args )
      {
        is( args... ); // TODO remove
      }

      template < typename... Args >
      void parseAssignmentExpression( Args... args )
      {
        is( args... ); // TODO remove
      }

      template < typename... Args >
      void parseTypeName( Args... args )
      {
        is( args... ); // TODO remove
      }

      private:
      Lex::Lexer &lexer;
    };
  } // end namespace Parse
} // end namespace C4

#endif
