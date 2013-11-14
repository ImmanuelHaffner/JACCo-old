//===--- Parser.h ---------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the Parser interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_PARSER_H
#define C4_PARSER_H

#include "../Lex/Token.h"
#include "../Lex/Lexer.h"
#include "../AST/AST.h"
#include "../AST/Identifier.h"
#include "../AST/Constant.h"
#include "../AST/StringLiteral.h"

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

      inline bool is()
      {
        return false;
      }

      inline bool is( Lex::TokenKind tKind )
      {
        return lexer.peek().kind == tKind;
      }

      inline bool is( std::string const &s )
      {
        return is( s.c_str() );
      }

      inline bool is( char const * const s )
      {
        return lexer.peek().text == s;
      }

      template < typename T, typename... Args >
        bool is( T t, Args... args )
        {
          return is( t ) || is( args... );
        }

      bool match( Lex::TokenKind tKind );
      bool match( char const * const s );

      inline bool match( std::string const &s )
      {
        return match( s.c_str() );
      }

      void until() {}

      template < typename... Args >
        void until( Args... args )
        {
          while ( ! is( args... ) )
            lexer.get();
        }

      template < typename T >
        void accept( T t )
        {
          if ( match( t ) )
            lexer.get();
        }

      template < typename T, typename... Args >
        void accept( T t, Args... args )
        {
          if ( match( t ) )
            lexer.get();
          else
            until( args... );
        }

      /// Parses the tokens returned by the lexer, and construct the
      /// corresponding AST.
      ///
      /// NOTE: This function may prompt errors/warnings to the console.
      ///
      /// \return the AST of the input
      AST::ASTNode & parse();

      /*
       *
       * Parser Sub Functions
       *
       */

#define __NODE( type ) *( new AST::ASTNode( AST::ASTType:: type ) )
#define __ILLEGAL __NODE( ILLEGAL )

      template < typename... Args >
      AST::ASTNode & parseIdentifier( Args... args )
      {
        if ( match( Lex::TokenKind::IDENTIFIER ) )
        {
          return *( new AST::Identifier( lexer.get() ) );
        }
        until( args... );
        return __ILLEGAL;
      }

      template < typename... Args >
      AST::ASTNode & parseConstant( Args... args )
      {
        if ( match( Lex::TokenKind::CONSTANT ) )
        {
          return *( new AST::Constant( lexer.get() ) );
        }
        until( args... );
        return __ILLEGAL;
      }

      template < typename... Args >
      AST::ASTNode & parseStringLiteral( Args... args )
      {
        if ( match( Lex::TokenKind::STRING_LITERAL ) )
        {
          return *( new AST::StringLiteral( lexer.get() ) );
        }
        until( args... );
        return __ILLEGAL;
      }

      template < typename... Args >
      AST::ASTNode & parsePrimaryExpression( Args... args )
      {
        if ( is( Lex::TokenKind::IDENTIFIER ) )
          return parseIdentifier( args... );
        if ( is( Lex::TokenKind::CONSTANT ) )
          return parseConstant( args... );
        if ( is( Lex::TokenKind::STRING_LITERAL ) )
          return parseStringLiteral( args... );
        
        accept( "(", ")" ); // TODO add FIRST(1) of 'expression'
        AST::ASTNode &node = parseExpression( args..., ")" );
        accept( ")", args... );
        return node;
      }

      template < typename... Args >
      AST::ASTNode & parsePostfixExpression( Args... args )
      {
        AST::ASTNode * sub = & parsePrimaryExpression( args..., "[", "(",
            ".", "->", "++", "--" );

        while ( is( "[", "(", ".", "->", "++", "--" ) )
        {
          AST::ASTNode * node = & __NODE( POSTFIX_EXPRESSION );
          node->append( *sub );
          sub = node;

          if ( is( "[" ) )
          {
            lexer.get();
            sub->append( parseExpression( args..., "]" ) );
            accept( "]", args... );
          }
          else if ( is( "(" ) )
          {
            lexer.get();
            if ( ! is( ")" ) )
              sub->append( parseArgumentExpressionList( args..., ")" ) );
            accept( ")", args... );
          }
          else if ( is( ".", "->" ) )
          {
            lexer.get();
            sub->append( parseIdentifier( args... ) );
          }
          else if ( is( "++", "--" ) )
          {
            lexer.get();
          }
          else
            break;
        }

        return *sub;
      }

      template < typename... Args >
      AST::ASTNode & parseArgumentExpressionList( Args... args )
      {
        AST::ASTNode * sub = & parseAssignmentExpression( args..., "," );

        while ( is( "," ) )
        {
          AST::ASTNode * node = & __NODE( POSTFIX_EXPRESSION );
          node->append( *sub );
          sub = node;

          lexer.get();
          sub->append( parseAssignmentExpression( args..., "," ) );
        }

        return *sub;
      }

      template < typename... Args >
      AST::ASTNode & parseUnaryExpression( Args... args )
      {
        if ( is( "++", "--" ) )
        {
          lexer.get();
          AST::ASTNode &node = __NODE( UNARY_EXPRESSION );
          node.append( parseUnaryExpression( args... ) );
          return node;
        }

        if ( is( "sizeof" ) )
        {
          lexer.get();
          AST::ASTNode &node = __NODE( UNARY_EXPRESSION );
          if ( is( "(" ) )
          {
            lexer.get();
            node.append( parseTypeName( args..., ")" ) );
            accept( ")", args... );
          }
          else
            node.append( parseUnaryExpression( args... ) );
          return node;
        }

        // unary_operator cast_expression
        if ( is( "&", "*", "+", "-", "~", "!" ) )
        {
          AST::ASTNode &node = __NODE( UNARY_EXPRESSION );
          node.append(
              parseUnaryOperator(
                args...,
                "!", "&", "(", "*", "+", "-", "~", "--", "++", "sizeof",
                Lex::TokenKind::IDENTIFIER,
                Lex::TokenKind::CONSTANT,
                Lex::TokenKind::STRING_LITERAL ) );
          node.append( parseCastExpression( args... ) );
          return node;
        }

        return parsePostfixExpression( args... );
      }
 
      template < typename... Args >
      AST::ASTNode & parseUnaryOperator( Args... args )
      {
        is( args... ); // TODO remove
        return __ILLEGAL;
      }

      template < typename... Args >
      AST::ASTNode & parseCastExpression( Args... args )
      {
        is( args... ); // TODO remove
        return __ILLEGAL;
      }

      template < typename... Args >
      AST::ASTNode & parseAssignmentOperator( Args... args )
      {
        is( args... ); // TODO remove
        return __ILLEGAL;
      }

      template < typename... Args >
      AST::ASTNode & parseExpression( Args... args )
      {
        is( args... ); // TODO remove
        return __ILLEGAL;
      }

      template < typename... Args >
      AST::ASTNode & parseStorageClassSpecifier( Args... args )
      {
        is( args... ); // TODO remove
        return __ILLEGAL;
      }

      template < typename... Args >
      AST::ASTNode & parseAssignmentExpression( Args... args )
      {
        is( args... ); // TODO remove
        return __ILLEGAL;
      }

      template < typename... Args >
      AST::ASTNode & parseTypeName( Args... args )
      {
        is( args... ); // TODO remove
        return __ILLEGAL;
      }

      private:
      Lex::Lexer &lexer;
    };
  } // end namespace Parse
} // end namespace C4

#endif
