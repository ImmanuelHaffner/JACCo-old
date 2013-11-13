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
#include "../Lex/KeywordToken.h"
#include "../Lex/PunctuatorToken.h"
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
      bool match( Lex::KeywordKind keyword );
      bool match( Lex::PunctuatorKind punctuator );
      bool match( std::string const &s );
      bool match( char const * const s );

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
      AST::ASTNode & parseUnaryOperator();
      AST::ASTNode & parseAssignmentOperator();
      AST::ASTNode & parseExpression();
      AST::ASTNode & parseStorageClassSpecifier();

      private:
      Lex::Lexer &lexer;
    };
  } // end namespace Parse
} // end namespace C4

#endif
