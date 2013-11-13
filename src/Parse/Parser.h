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

namespace C4
{
  namespace Parse
  {
    struct Parser
    {
      Parser( Lex::Lexer &lexer );
      ~Parser();

      template < typename T >
      void accept( T t );

      bool match( Lex::TokenKind tKind );

      inline bool match( char const * const s )
      {
        return lexer.peek().text == s;
      }

      inline bool match( std::string const &s )
      {
        return match( s.c_str() );
      }

      /// Parses the tokens returned by the lexer, and construct the
      /// corresponding AST.
      ///
      /// NOTE: This function may prompt errors/warnings to the console.
      ///
      /// \return the AST of the input
      AST::ASTNode & parse();

      AST::ASTNode & parseIdentifier();
      AST::ASTNode & parseConstant();
      AST::ASTNode & parseStringLiteral();
      AST::ASTNode & parsePrimaryExpression();
      AST::ASTNode & parsePostfixExpression();
      AST::ASTNode & parseArgumentExpressionList();
      AST::ASTNode & parseUnaryExpression();

      AST::ASTNode & parseUnaryOperator();
      AST::ASTNode & parseAssignmentOperator();
      AST::ASTNode & parseExpression();
      AST::ASTNode & parseStorageClassSpecifier();
      AST::ASTNode & parseAssignmentExpression();
      AST::ASTNode & parseTypeName();
      AST::ASTNode & parseCastExpression();

      private:
      Lex::Lexer &lexer;
    };
  } // end namespace Parse
} // end namespace C4

#endif
