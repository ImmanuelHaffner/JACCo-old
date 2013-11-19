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

#define PRIMARY_EXPRESSION \
  Lex::TokenKind::IDENTIFIER,\
  Lex::TokenKind::CONSTANT,\
  Lex::TokenKind::STRING_LITERAL,\
  "("

#define POSTFIX_EXPRESSION \
  PRIMARY_EXPRESSION

/*
#define ARGUMENT_EXPRESSION_LIST \
  ASSIGNMENT_EXPRESSION
  */

#define UNARY_EXPRESSION \
  POSTFIX_EXPRESSION,\
  "++",\
  "--",\
  UNARY_OPERATOR,\
  "sizeof"

#define UNARY_OPERATOR \
  "&",\
  "*",\
  "+",\
  "-",\
  "~",\
  "!"


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

// End First1

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
        return lexer.peek().kind == tKind;
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
        return lexer.peek().text == s;
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
        bool match( Args... args )
        {
          if ( ! is( args... ) )
          {
            Lex::Token &tok = lexer.peek();

            switch ( tok.kind )
            {
              case Lex::TokenKind::ILLEGAL:
                {
                  std::ostringstream oss;
                  oss << tok.pos << " " << tok;
                  errorf( tok.pos, "%s", oss.str().c_str() );
                  return false;
                }

              case Lex::TokenKind::END_OF_FILE:
                {
                  std::ostringstream oss;
                  oss << "unexpected end-of-file, expected one of: ";
                  pout( oss, args... );
                  errorf( tok.pos, "%s", oss.str().c_str() );
                  return false;
                }

              default:
                {
                  std::ostringstream oss;
                  oss << "unexpected '" << tok.text << "', expected one of: ";
                  pout( oss, args... );
                  errorf( tok.pos, "%s", oss.str().c_str() );
                  return false;
                }
            }
          }
          return true;
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
            lexer.get();
        }

      /// Checks whether the token peeked by the lexer matches the ffirst
      /// argument, by invoking match( ... ). If the token matches, gets the
      /// token from the lexer, else, invokes until( ... ) with the given follow
      /// set.
      template < typename T, typename... Args >
        void accept( T t, Args... args )
        {
          bool b = match( t );
          lexer.get();
          if ( ! b )
            until( args... );
        }

      /// Parses the tokens returned by the lexer, and construct the
      /// corresponding AST.
      ///
      /// NOTE: This function may prompt errors/warnings to the console.
      inline void parse()
      {
        parseUnaryExpression( Lex::TokenKind::END_OF_FILE );
      }

      /*
       *
       * Parser Sub Functions
       *
       */

      template < typename... Args >
      void parsePrimaryExpression( Args... args )
      {
        if ( match( PRIMARY_EXPRESSION ) )
        {
          if ( is( "(" ) )
          {
            lexer.get();
            parseExpression( ")", args... );
            accept( ")", args... );
          }
          else
            lexer.get();
        }
        else
          until( args... );
      }

      template < typename... Args >
      void parsePostfixExpression( Args... args )
      {
        parsePrimaryExpression( "[", "(", ".", "->", "++", "--", args... );

        while ( true )
        {
          if ( is( "[" ) )
          {
            lexer.get();
            parseExpression( "]", args... );
            accept( "]", args... );
          }
          else if ( is( "(" ) )
          {
            lexer.get();
            if ( ! is( ")" ) )
              parseArgumentExpressionList( ")", args... );
            accept( ")", args... );
          }
          else if ( is( ".", "->" ) )
          {
            lexer.get();
            accept( Lex::TokenKind::IDENTIFIER, args... );
          }
          else if ( is( "++", "--" ) )
          {
            lexer.get();
          }
          else
            break;
        }
      }

      template < typename... Args >
      void parseArgumentExpressionList( Args... args )
      {
        parseAssignmentExpression( ",", args... );

        while ( is( "," ) )
        {
          lexer.get();
          parseAssignmentExpression( ",", args... );
        }
      }

      template < typename... Args >
      void parseUnaryExpression( Args... args )
      {
        if ( is( "++", "--" ) )
        {
          lexer.get();
          parseUnaryExpression( args... );
        }
        else if ( is( "sizeof" ) )
        {
          lexer.get();
          if ( is( "(" ) )
          {
            lexer.get();
            parseTypeName( ")", args... );
            accept( ")", args... );
          }
          else
            parseUnaryExpression( args... );
        }
        // unary_operator cast_expression
        else if ( is( UNARY_OPERATOR ) )
        {
          lexer.get();
          parseCastExpression( args... );
        }
        else
          parsePostfixExpression( args... );
      }
 
      template < typename... Args >
      void parseCastExpression( Args... args )
      {
        if ( is( "(" ) )
        {
          lexer.get();
          parseTypeName( ")", args... );
          accept( ")" );
        }
        else
          parseUnaryExpression( args... );
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
