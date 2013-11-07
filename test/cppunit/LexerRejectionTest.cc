//===--- LexerRejectionTest.cc --------------------------------------------===//
//
//	~~~ The C4 Compiler TestSuite ~~~
//
//===----------------------------------------------------------------------===//

#include "LexerRejectionTest.h"

#include "../../src/Lex/Lexer.h"
#include "../../src/Lex/KeywordToken.h"
#include "../../src/Lex/PunctuatorToken.h"
#include "../../src/Lex/IllegalToken.h"


// register this test 
CPPUNIT_TEST_SUITE_REGISTRATION ( LexerRejectionTest );

using namespace C4;
using namespace Lex;

void LexerRejectionTest::setUp()
{
}

void LexerRejectionTest::tearDown()
{
}


void LexerRejectionTest::testEmptyCharConst()
{
  // redirect stdin
  std::istringstream stream( "''''" );
  std::streambuf * cin_bak = std::cin.rdbuf( stream.rdbuf() );

  Lexer lexer;
  Token * token;
  IllegalToken * itok;


	// ''
  token = & lexer.get();
  CPPUNIT_ASSERT( token->kind  == TokenKind::ILLEGAL );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "''" );
  itok = static_cast< IllegalToken* >( token );
  CPPUNIT_ASSERT( itok->iKind == IllegalTokenKind::EMPTY_CHARACTER_CONSTANT );
  delete token;

	// ''
  token = & lexer.get();
  CPPUNIT_ASSERT( token->kind  == TokenKind::ILLEGAL );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 3u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "''" );
  itok = static_cast< IllegalToken* >( token );
  CPPUNIT_ASSERT( itok->iKind == IllegalTokenKind::EMPTY_CHARACTER_CONSTANT );
  delete token;


  // restode stdin
  std::cin.rdbuf( cin_bak );
}

void LexerRejectionTest::testIllegalIdentifiers()
{
  // redirect stdin
  std::istringstream stream( "12a 1_ 1_2 1a2" );
	std::streambuf * cin_bak = std::cin.rdbuf( stream.rdbuf() );

  Lexer lexer;
  Token * token;
  IllegalToken * itok;


	// 12a
  token = & lexer.get();
  CPPUNIT_ASSERT( token->kind  == TokenKind::ILLEGAL );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "12a" );
  itok = static_cast< IllegalToken* >( token );
  CPPUNIT_ASSERT( itok->iKind == IllegalTokenKind::IDENTIFIER );
  delete token;

	// 1_
  token = & lexer.get();
  CPPUNIT_ASSERT( token->kind  == TokenKind::ILLEGAL );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 5u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "1_" );
  itok = static_cast< IllegalToken* >( token );
  CPPUNIT_ASSERT( itok->iKind == IllegalTokenKind::IDENTIFIER );
  delete token;

	// 1_2
  token = & lexer.get();
  CPPUNIT_ASSERT( token->kind  == TokenKind::ILLEGAL );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 8u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "1_2" );
  itok = static_cast< IllegalToken* >( token );
  CPPUNIT_ASSERT( itok->iKind == IllegalTokenKind::IDENTIFIER );
  delete token;

	// 1a2
  token = & lexer.get();
  CPPUNIT_ASSERT( token->kind  == TokenKind::ILLEGAL );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 12u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "1a2" );
  itok = static_cast< IllegalToken* >( token );
  CPPUNIT_ASSERT( itok->iKind == IllegalTokenKind::IDENTIFIER );
  delete token;


  // restode stdin
  std::cin.rdbuf( cin_bak );
}

void LexerRejectionTest::testIllegalComments()
{
  // redirect stdin
  std::istringstream stream( "/*" );
  std::streambuf * cin_bak = std::cin.rdbuf( stream.rdbuf() );

  Lexer lexer;
  Token * token;
  IllegalToken * itok;


  token = & lexer.get();
  CPPUNIT_ASSERT( token->kind == TokenKind::ILLEGAL );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.column );
  itok = static_cast< IllegalToken* >( token );
  CPPUNIT_ASSERT( itok->iKind == IllegalTokenKind::MISSING_COMMENT_TERMINATOR );
  delete token;


  // redirect stdin
  stream.str( "\n/*/" );
  std::cin.rdbuf( stream.rdbuf() );

  token = & lexer.get();
  CPPUNIT_ASSERT( token->kind == TokenKind::ILLEGAL );
  CPPUNIT_ASSERT_EQUAL( 2u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.column );
  itok = static_cast< IllegalToken* >( token );
  CPPUNIT_ASSERT( itok->iKind == IllegalTokenKind::MISSING_COMMENT_TERMINATOR );
  delete token;


  // restode stdin
  std::cin.rdbuf( cin_bak );
}
