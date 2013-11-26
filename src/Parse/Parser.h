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
        //  Must never return 0.
        //

      default: return -1;
    }
  } // end getBinOpPrecedence

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
        bool is( T t, Args... args );

      /// If the current token is "like" t, i.e. a call to is( t ) would return
      /// true, gets the next token, otherwise prints an error message.
      template < typename T >
        void accept( T t );

      /// If the current token is "like" args, i.e. a call to is( t ) would
      /// return true, gets the next token, otherwise prints an error message.
      template < typename... Args >
        void accept( Args... args );

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

      //
      //  Expressions
      //

      AST::Expression & parsePrimaryExpression();
      AST::Expression & parseArgumentExpressionList();
      AST::Expression & parsePostfixExpression();
      AST::Expression & parseUnaryExpression();
      AST::Expression & parseCastExpression();
      AST::Expression & parseBinaryExpression();
      AST::Expression & parseBinOpRHS( int exprPrec, AST::Expression &lhs );
      AST::Expression & parseConditionalExpression();
      AST::Expression & parseAssignmentExpression();

      /// Parses an expression.
      ///
      /// \return the parsed expression
      AST::Expression & parseExpression();
      inline AST::Expression & parseConstantExpression()
      {
        return parseConditionalExpression();
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
      AST::Declaration & parseTypeName();
      AST::Declaration & parseAbstractDeclarator();
      AST::Declaration & parseDirectAbstractDeclarator();
      AST::Declaration & parseMaybeAbstractDeclarator();
      AST::Declaration & parseDirectMaybeAbstractDeclarator();

      AST::Declaration & parseInitializer();
      AST::Declaration & parseInitializerList();

      //
      //  Statements
      //

      AST::Statement & parseStatement();
      AST::Statement & parseLabeledStatement();
      AST::Statement & parseCompoundStatement();
      AST::Statement & parseDeclarationList();
      AST::Statement & parseStatementList();
      AST::Statement & parseExpressionStatement();
      AST::Statement & parseSelectionStatement();
      AST::Statement & parseIterationStatement();
      AST::Statement & parseJumpStatement();

      AST::Statement & parseTranslationUnit();
      AST::Statement & parseExternalDeclaration();
      AST::Statement & parseFunctionDefinition();


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
          oss << "unexpected " << *current << ", expected '" << t << "'";
          errorf( current->pos, "%s", oss.str().c_str() );
        }
        else
          readNextToken();
      }

    template < typename T >
      static void _print( std::ostream &out, T t )
      {
        out << t;
      }

    template < typename T, typename... Args >
      static void _print( std::ostream &out, T t, Args... args )
      {
        out << t << "', '";
        _print( out, args... );
      }

    template < typename... Args >
      static void print( std::ostream &out, Args... args )
      {
        out << "'"; _print( out, args... ); out << "'";
      }

    template < typename... Args >
      void Parser::accept( Args... args )
      {
        if ( ! is( args... ) )
        {
          std::ostringstream oss;
          oss << "unexpected " << *current << ", expected one of '";
          print( oss, args... );
          oss << "'";
          errorf( current->pos, "%s", oss.str().c_str() );
        }
        else
          readNextToken();
      }
  } // end namespace Parse
} // end namespace C4

#endif
