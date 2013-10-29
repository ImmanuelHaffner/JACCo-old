//===--- LexerTest.cc -----------------------------------------------------===//
//
//	~~~ The C4 Compiler TestSuite ~~~
//
//===----------------------------------------------------------------------===//

#include "LexerTest.h"

#include "../src/Lex/Lexer.h"
#include "../src/Lex/KeywordToken.h"


// register this test 
CPPUNIT_TEST_SUITE_REGISTRATION ( LexerTest );

using namespace C4;
using namespace Lex;

void LexerTest::setUp()
{
}

void LexerTest::tearDown()
{
}


void LexerTest::testConstructor()
{
	char const * const fileName = "resource/allowedCharacters.c";

	Lexer lexer( fileName );

	// check file name
	CPPUNIT_ASSERT( lexer.fileName.compare( fileName ) == 0 );

	// check pos
	CPPUNIT_ASSERT( strcmp( fileName, lexer.getPos().name ) == 0 );
	CPPUNIT_ASSERT_EQUAL( 1u, lexer.getPos().line );
	CPPUNIT_ASSERT_EQUAL( 1u, lexer.getPos().column );

  Lexer lexer2;
	// check file name
	CPPUNIT_ASSERT( lexer2.fileName.compare( "<stdin>" ) == 0 );

	// check pos
	CPPUNIT_ASSERT_EQUAL( 1u, lexer2.getPos().line );
	CPPUNIT_ASSERT_EQUAL( 1u, lexer2.getPos().column );
}

void LexerTest::testSkip()
{
  std::istringstream stream( "a  b\nc \n d\r\ne _f1" );

  // redirect stdin
  std::streambuf * cin_bak = std::cin.rdbuf( stream.rdbuf() );

  Lexer lexer;

	// a
  CPPUNIT_ASSERT_EQUAL( 'a', lexer.current() );
	CPPUNIT_ASSERT_EQUAL( 1u, lexer.getPos().line );
	CPPUNIT_ASSERT_EQUAL( 1u, lexer.getPos().column );

	// b
	lexer.skip();

  CPPUNIT_ASSERT_EQUAL( 'b', lexer.current() );
	CPPUNIT_ASSERT_EQUAL( 1u, lexer.getPos().line );
	CPPUNIT_ASSERT_EQUAL( 4u, lexer.getPos().column );

	// c
	lexer.skip();

	CPPUNIT_ASSERT_EQUAL( 2u, lexer.getPos().line );
	CPPUNIT_ASSERT_EQUAL( 1u, lexer.getPos().column );

	// d
	lexer.skip();

	CPPUNIT_ASSERT_EQUAL( 3u, lexer.getPos().line );
	CPPUNIT_ASSERT_EQUAL( 2u, lexer.getPos().column );

	// e
	lexer.skip();

	CPPUNIT_ASSERT_EQUAL( 4u, lexer.getPos().line );
	CPPUNIT_ASSERT_EQUAL( 1u, lexer.getPos().column );

	// _
	lexer.skip();

	CPPUNIT_ASSERT_EQUAL( 4u, lexer.getPos().line );
	CPPUNIT_ASSERT_EQUAL( 3u, lexer.getPos().column );

	// f
	lexer.skip();

	CPPUNIT_ASSERT_EQUAL( 4u, lexer.getPos().line );
	CPPUNIT_ASSERT_EQUAL( 4u, lexer.getPos().column );

	// 1
	lexer.skip();

	CPPUNIT_ASSERT_EQUAL( 4u, lexer.getPos().line );
	CPPUNIT_ASSERT_EQUAL( 5u, lexer.getPos().column );


  // restode stdin
  std::cin.rdbuf( cin_bak );
}

void LexerTest::testReadIdentifier()
{
  std::istringstream stream( "a b\nc \n d\r\ne f1 _f2" );

  // redirect stdin
  std::streambuf * cin_bak = std::cin.rdbuf( stream.rdbuf() );

  Lexer lexer;
  Token * token;

  // a
  token = & lexer.readKeywordOrIdentifier();
  CPPUNIT_ASSERT( token->kind  == TokenKind::IDENTIFIER );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "a" );
  delete token;
  lexer.skip();

  // b
  token = & lexer.readKeywordOrIdentifier();
  CPPUNIT_ASSERT( token->kind  == TokenKind::IDENTIFIER );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 3u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "b" );
  delete token;
  lexer.skip();

  // c
  token = & lexer.readKeywordOrIdentifier();
  CPPUNIT_ASSERT( token->kind  == TokenKind::IDENTIFIER );
  CPPUNIT_ASSERT_EQUAL( 2u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "c" );
  delete token;
  lexer.skip();

  // d
  token = & lexer.readKeywordOrIdentifier();
  CPPUNIT_ASSERT( token->kind  == TokenKind::IDENTIFIER );
  CPPUNIT_ASSERT_EQUAL( 3u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 2u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "d" );
  delete token;
  lexer.skip();

  // e
  token = & lexer.readKeywordOrIdentifier();
  CPPUNIT_ASSERT( token->kind  == TokenKind::IDENTIFIER );
  CPPUNIT_ASSERT_EQUAL( 4u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "e" );
  delete token;
  lexer.skip();

  // f1
  token = & lexer.readKeywordOrIdentifier();
  CPPUNIT_ASSERT( token->kind  == TokenKind::IDENTIFIER );
  CPPUNIT_ASSERT_EQUAL( 4u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 3u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "f1" );
  delete token;
  lexer.skip();

  // _f2
  token = & lexer.readKeywordOrIdentifier();
  CPPUNIT_ASSERT( token->kind  == TokenKind::IDENTIFIER );
  CPPUNIT_ASSERT_EQUAL( 4u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 6u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "_f2" );
  delete token;
  lexer.skip();


  // restode stdin
  std::cin.rdbuf( cin_bak );
}

void LexerTest::testReadKeywords()
{
  std::istringstream stream( "auto break\nconst \n int\r\ncontinue while for" );

  // redirect stdin
  std::streambuf * cin_bak = std::cin.rdbuf( stream.rdbuf() );

  Lexer lexer;
  Token * token;
  KeywordToken * keyword;

  // auto
  token = & lexer.readKeywordOrIdentifier();
  CPPUNIT_ASSERT( token->kind  == TokenKind::KEYWORD );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "auto" );
  keyword = dynamic_cast< KeywordToken* >( token );
  CPPUNIT_ASSERT( keyword->keyword == KeywordKind::AUTO );
  delete token;
  lexer.skip();

  // break
  token = & lexer.readKeywordOrIdentifier();
  CPPUNIT_ASSERT( token->kind  == TokenKind::KEYWORD );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 6u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "break" );
  keyword = dynamic_cast< KeywordToken* >( token );
  CPPUNIT_ASSERT( keyword->keyword == KeywordKind::BREAK );
  delete token;
  lexer.skip();

  // const
  token = & lexer.readKeywordOrIdentifier();
  CPPUNIT_ASSERT( token->kind  == TokenKind::KEYWORD );
  CPPUNIT_ASSERT_EQUAL( 2u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "const" );
  keyword = dynamic_cast< KeywordToken* >( token );
  CPPUNIT_ASSERT( keyword->keyword == KeywordKind::CONST );
  delete token;
  lexer.skip();

  // int
  token = & lexer.readKeywordOrIdentifier();
  CPPUNIT_ASSERT( token->kind  == TokenKind::KEYWORD );
  CPPUNIT_ASSERT_EQUAL( 3u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 2u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "int" );
  keyword = dynamic_cast< KeywordToken* >( token );
  CPPUNIT_ASSERT( keyword->keyword == KeywordKind::INT );
  delete token;
  lexer.skip();

  // continue
  token = & lexer.readKeywordOrIdentifier();
  CPPUNIT_ASSERT( token->kind  == TokenKind::KEYWORD );
  CPPUNIT_ASSERT_EQUAL( 4u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "continue" );
  keyword = dynamic_cast< KeywordToken* >( token );
  CPPUNIT_ASSERT( keyword->keyword == KeywordKind::CONTINUE );
  delete token;
  lexer.skip();

  // while
  token = & lexer.readKeywordOrIdentifier();
  CPPUNIT_ASSERT( token->kind  == TokenKind::KEYWORD );
  CPPUNIT_ASSERT_EQUAL( 4u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 10u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "while" );
  keyword = dynamic_cast< KeywordToken* >( token );
  CPPUNIT_ASSERT( keyword->keyword == KeywordKind::WHILE );
  delete token;
  lexer.skip();

  // for
  token = & lexer.readKeywordOrIdentifier();
  CPPUNIT_ASSERT( token->kind  == TokenKind::KEYWORD );
  CPPUNIT_ASSERT_EQUAL( 4u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 16u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "for" );
  keyword = dynamic_cast< KeywordToken* >( token );
  CPPUNIT_ASSERT( keyword->keyword == KeywordKind::FOR );
  delete token;
  lexer.skip();


  // restode stdin
  std::cin.rdbuf( cin_bak );
}
