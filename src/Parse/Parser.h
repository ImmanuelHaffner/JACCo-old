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
    class Parser
    {
      Parser( Lex::Lexer &lexer );
      ~Parser();

      template < typename T >
      void accept( T t );

      bool _accept( Lex::TokenKind tKind );
      bool _accept( Lex::KeywordKind keyword );
      bool _accept( Lex::PunctuatorKind punctuator );
      bool _accept( std::string const s );
      bool _accept( char const * const s );

      /// Parses the tokens returned by the lexer, and construct the
      /// corresponding AST.
      ///
      /// NOTE: This function may prompt errors/warnings to the console.
      ///
      /// \return the AST of the input
      AST::ASTNode & parse();

      AST::ASTNode & parsePrimaryExpression();
      AST::ASTNode & parseUnaryOperator();
      AST::ASTNode & parseAssignmentOperator();
      AST::ASTNode & parseExpression();

      private:
      Lex::Lexer &lexer;
    };
  } // end namespace Parse
} // end namespace C4

#endif
