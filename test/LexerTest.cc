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
  lexer.step();
	lexer.skip();

  CPPUNIT_ASSERT_EQUAL( 'b', lexer.current() );
	CPPUNIT_ASSERT_EQUAL( 1u, lexer.getPos().line );
	CPPUNIT_ASSERT_EQUAL( 4u, lexer.getPos().column );

	// c
  lexer.step();
	lexer.skip();

	CPPUNIT_ASSERT_EQUAL( 2u, lexer.getPos().line );
	CPPUNIT_ASSERT_EQUAL( 1u, lexer.getPos().column );

	// d
  lexer.step();
	lexer.skip();

	CPPUNIT_ASSERT_EQUAL( 3u, lexer.getPos().line );
	CPPUNIT_ASSERT_EQUAL( 2u, lexer.getPos().column );

	// e
  lexer.step();
	lexer.skip();

	CPPUNIT_ASSERT_EQUAL( 4u, lexer.getPos().line );
	CPPUNIT_ASSERT_EQUAL( 1u, lexer.getPos().column );

	// _
  lexer.step();
	lexer.skip();

	CPPUNIT_ASSERT_EQUAL( 4u, lexer.getPos().line );
	CPPUNIT_ASSERT_EQUAL( 3u, lexer.getPos().column );

	// f
  lexer.step();
	lexer.skip();

	CPPUNIT_ASSERT_EQUAL( 4u, lexer.getPos().line );
	CPPUNIT_ASSERT_EQUAL( 4u, lexer.getPos().column );

	// 1
  lexer.step();
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

void LexerTest::testReadNumericalConstant()
{
  std::istringstream stream( "1 23\n4 \n 5\r\n67 8 90" );

  // redirect stdin
  std::streambuf * cin_bak = std::cin.rdbuf( stream.rdbuf() );

  Lexer lexer;
  Token * token;

  // 1
  token = & lexer.readNumericalConstant();
  CPPUNIT_ASSERT( token->kind  == TokenKind::CONSTANT );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "1" );
  delete token;
  lexer.skip();

  // 23
  token = & lexer.readNumericalConstant();
  CPPUNIT_ASSERT( token->kind  == TokenKind::CONSTANT );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 3u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "23" );
  delete token;
  lexer.skip();

  // 4
  token = & lexer.readNumericalConstant();
  CPPUNIT_ASSERT( token->kind  == TokenKind::CONSTANT );
  CPPUNIT_ASSERT_EQUAL( 2u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "4" );
  delete token;
  lexer.skip();

  // 5
  token = & lexer.readNumericalConstant();
  CPPUNIT_ASSERT( token->kind  == TokenKind::CONSTANT );
  CPPUNIT_ASSERT_EQUAL( 3u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 2u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "5" );
  delete token;
  lexer.skip();

  // 67
  token = & lexer.readNumericalConstant();
  CPPUNIT_ASSERT( token->kind  == TokenKind::CONSTANT );
  CPPUNIT_ASSERT_EQUAL( 4u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "67" );
  delete token;
  lexer.skip();

  // 8
  token = & lexer.readNumericalConstant();
  CPPUNIT_ASSERT( token->kind  == TokenKind::CONSTANT );
  CPPUNIT_ASSERT_EQUAL( 4u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 4u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "8" );
  delete token;
  lexer.skip();

  // 90
  token = & lexer.readNumericalConstant();
  CPPUNIT_ASSERT( token->kind  == TokenKind::CONSTANT );
  CPPUNIT_ASSERT_EQUAL( 4u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 6u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "90" );
  delete token;
  lexer.skip();


  // restode stdin
  std::cin.rdbuf( cin_bak );
}

void LexerTest::testReadCharacterConstant()
{
  std::istringstream stream( "'a' 'b'\n'c' \n 'd'\r\n'e' '\\n' '\\\\'" );

  // redirect stdin
  std::streambuf * cin_bak = std::cin.rdbuf( stream.rdbuf() );

  Lexer lexer;
  Token * token;


  // a
  token = & lexer.readCharacterConstantOrStringLiteral();
  CPPUNIT_ASSERT( token->kind  == TokenKind::CONSTANT );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "'a'" );
  delete token;
  lexer.skip();

  // b
  token = & lexer.readCharacterConstantOrStringLiteral();
  CPPUNIT_ASSERT( token->kind  == TokenKind::CONSTANT );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 5u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "'b'" );
  delete token;
  lexer.skip();

  // c
  token = & lexer.readCharacterConstantOrStringLiteral();
  CPPUNIT_ASSERT( token->kind  == TokenKind::CONSTANT );
  CPPUNIT_ASSERT_EQUAL( 2u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "'c'" );
  delete token;
  lexer.skip();

  // d
  token = & lexer.readCharacterConstantOrStringLiteral();
  CPPUNIT_ASSERT( token->kind  == TokenKind::CONSTANT );
  CPPUNIT_ASSERT_EQUAL( 3u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 2u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "'d'" );
  delete token;
  lexer.skip();

  // e
  token = & lexer.readCharacterConstantOrStringLiteral();
  CPPUNIT_ASSERT( token->kind  == TokenKind::CONSTANT );
  CPPUNIT_ASSERT_EQUAL( 4u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "'e'" );
  delete token;
  lexer.skip();

  // \n
  token = & lexer.readCharacterConstantOrStringLiteral();
  CPPUNIT_ASSERT( token->kind  == TokenKind::CONSTANT );
  CPPUNIT_ASSERT_EQUAL( 4u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 5u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "'\\n'" );
  delete token;
  lexer.skip();

  // \\ (text to avoid two-line comment)
  token = & lexer.readCharacterConstantOrStringLiteral();
  CPPUNIT_ASSERT( token->kind  == TokenKind::CONSTANT );
  CPPUNIT_ASSERT_EQUAL( 4u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 10u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "'\\\\'" );
  delete token;
  lexer.skip();


  // restode stdin
  std::cin.rdbuf( cin_bak );
}
