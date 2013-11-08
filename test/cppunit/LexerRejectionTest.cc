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
