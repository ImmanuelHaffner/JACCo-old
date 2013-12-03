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
      Lex::Token const * getCurTok() { return current; }
      Lex::Token const * getNextTok() { return next; }


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

      AST::Expr const * parsePrimaryExpr();
      AST::Expr const * parsePostfixExpr();
      AST::Expr const * parseArgumentExprList();
      AST::Expr const * parseUnaryExpr();
      AST::Expr const * parseCastExpr();
      AST::Expr const * parseBinaryExpr();
      AST::Expr const * parseBinOpRHS( int exprPrec,
          AST::Expr const * const lhs );
      AST::Expr const * parseConditionalExpr();
      AST::Expr const * parseAssignmentExpr();

      /// Parses an expression.
      ///
      /// \return the parsed expression
      AST::Expr const * parseExpr();
      inline AST::Expr const * parseConstantExpr()
      {
        return parseConditionalExpr();
      }

      //
      // Declarations
      //

      AST::Decl const * parseDecl();
      AST::Decl const * parseDeclSpecifiers();
      AST::Decl const * parseInitDeclaratorList();
      AST::Decl const * parseInitDeclarator();
      AST::Decl const * parseTypeSpecifier();
      AST::Decl const * parseStructOrUnionSpecifier();
      AST::Decl const * parseStructOrUnion();
      AST::Decl const * parseStructDeclList();
      AST::Decl const * parseStructDecl();
      AST::Decl const * parseSpecifierQualifierList();
      AST::Decl const * parseStructDeclaratorList();
      AST::Decl const * parseStructDeclarator();
      AST::Decl const * parseDeclarator();
      AST::Decl const * parseDirectDeclarator();
      AST::Decl const * parsePointer();
      AST::Decl const * parseParameterTypeList();
      AST::Decl const * parseParameterList();
      AST::Decl const * parseParameterDecl();
      AST::Decl const * parseIdentifierList();
      AST::Decl const * parseAbstractDeclarator();
      AST::Decl const * parseDirectAbstractDeclarator();
      AST::Decl const * parseMaybeAbstractDeclarator();
      AST::Decl const * parseDirectMaybeAbstractDeclarator();

      AST::Decl const * parseInitializer();
      AST::Decl const * parseInitializerList();

      //
      //  Type
      //

      AST::Type const * parseTypeName();

      //
      //  Statements
      //

      AST::Stmt const * parseStmt();
      AST::Stmt const * parseLabeledStmt();
      AST::Stmt const * parseCompoundStmt();
      AST::Stmt const * parseDeclList();
      AST::Stmt const * parseStmtList();
      AST::Stmt const * parseExprStmt();
      AST::Stmt const * parseSelectionStmt();
      AST::Stmt const * parseIterationStmt();
      AST::Stmt const * parseJumpStmt();

      AST::Stmt const * parseTranslationUnit();
      AST::Stmt const * parseExternalDecl();
    }; // end struct Parser
  } // end namespace Parse
} // end namespace C4

#endif
