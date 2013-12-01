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


namespace C4
{
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
      Lex::Token const & getCurTok() { return *current; }
      Lex::Token const & getNextTok() { return *next; }


      private:
      Lex::Lexer &lexer;
      Lex::Token const * current;
      Lex::Token const * next;


      //===----------------------------------------------------------------===//
      //
      //  Parser Helper Functions
      //
      //===----------------------------------------------------------------===//

      /// If the current token is a binary operator, returns its precedence,
      /// otherwise -1 is returned.
      /// Will never return 0.
      ///
      /// \return the precedence of the current token
      int getTokenPrecedence();

      /// This functions moves sets 'current' to 'next', and sets 'next' to the
      /// token returned from the lexer.
      /// This function offers a small, fixed-size token buffer.
      void readNextToken();

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
        bool is( T t, Args... args )
        {
          return is( t ) || is( args... );
        }

      /// If the current token is of kind tk, i.e. a call to is( tk ) would
      /// return true, gets the next token, otherwise prints an error message.
      bool accept( Lex::TK tk );


      //===----------------------------------------------------------------===//
      //
      //  Parser Sub Functions
      //
      //  These functions parse particular rules of the grammar, e.g.
      //  declarations or expressions.
      //
      //===----------------------------------------------------------------===//

      //
      //  Expressions
      //

      AST::Expr & parsePrimaryExpr();
      AST::Expr & parsePostfixExpr();
      AST::Expr & parseArgumentExprList();
      AST::Expr & parseUnaryExpr();
      AST::Expr & parseCastExpr();
      AST::Expr & parseBinaryExpr();
      AST::Expr & parseBinOpRHS( int exprPrec, AST::Expr &lhs );
      AST::Expr & parseConditionalExpr();
      AST::Expr & parseAssignmentExpr();

      /// Parses an expression.
      ///
      /// \return the parsed expression
      AST::Expr & parseExpr();
      inline AST::Expr & parseConstantExpr()
      {
        return parseConditionalExpr();
      }

      //
      // Declarations
      //

      AST::Declaration & parseDeclaration();
      AST::Declaration & parseDeclarationSpecifiers();
      AST::Declaration & parseInitDeclaratorList();
      AST::Declaration & parseInitDeclarator();
      AST::Declaration & parseTypeSpecifier();
      AST::Declaration & parseStructOrUnionSpecifier();
      AST::Declaration & parseStructOrUnion();
      AST::Declaration & parseStructDeclarationList();
      AST::Declaration & parseStructDeclaration();
      AST::Declaration & parseSpecifierQualifierList();
      AST::Declaration & parseStructDeclaratorList();
      AST::Declaration & parseStructDeclarator();
      AST::Declaration & parseDeclarator();
      AST::Declaration & parseDirectDeclarator();
      AST::Declaration & parsePointer();
      AST::Declaration & parseParameterTypeList();
      AST::Declaration & parseParameterList();
      AST::Declaration & parseParameterDeclaration();
      AST::Declaration & parseIdentifierList();
      AST::Declaration & parseAbstractDeclarator();
      AST::Declaration & parseDirectAbstractDeclarator();
      AST::Declaration & parseMaybeAbstractDeclarator();
      AST::Declaration & parseDirectMaybeAbstractDeclarator();

      AST::Declaration & parseInitializer();
      AST::Declaration & parseInitializerList();

      //
      //  Type
      //

      AST::Type & parseTypeName();

      //
      //  Statements
      //

      AST::Statement & parseStatement();
      AST::Statement & parseLabeledStatement();
      AST::Statement & parseCompoundStatement();
      AST::Statement & parseDeclarationList();
      AST::Statement & parseStatementList();
      AST::Statement & parseExprStatement();
      AST::Statement & parseSelectionStatement();
      AST::Statement & parseIterationStatement();
      AST::Statement & parseJumpStatement();

      AST::Statement & parseTranslationUnit();
      AST::Statement & parseExternalDeclaration();
    }; // end struct Parser
  } // end namespace Parse
} // end namespace C4

#endif
