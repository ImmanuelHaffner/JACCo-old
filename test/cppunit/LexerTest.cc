//===--- LexerTest.cc -----------------------------------------------------===//
//
//	~~~ The C4 Compiler TestSuite ~~~
//
//===----------------------------------------------------------------------===//

#include "LexerTest.h"

#include "../../src/Lex/Lexer.h"
#include "../../src/Lex/IllegalToken.h"


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
  std::istringstream stream( "a  b\nc \n d\r\ne _f1\rg" );

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

	// g
  lexer.step();
	lexer.skip();

	CPPUNIT_ASSERT_EQUAL( 5u, lexer.getPos().line );
	CPPUNIT_ASSERT_EQUAL( 1u, lexer.getPos().column );


  // restode stdin
  std::cin.rdbuf( cin_bak );
}

void LexerTest::testEof()
{
  // redirect stdin
  std::istringstream stream( "" );
  std::streambuf * cin_bak = std::cin.rdbuf( stream.rdbuf() );

  Lexer lexer;
  Token * token;

  token = & lexer.get();
  CPPUNIT_ASSERT( token->kind == TokenKind::END_OF_FILE );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.column );

  token = & lexer.get();
  CPPUNIT_ASSERT( token->kind == TokenKind::END_OF_FILE );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.column );


  // restode stdin
  std::cin.rdbuf( cin_bak );
}

void LexerTest::testPeek()
{
  Lexer lexer;

  // redirect stdin
  std::istringstream stream( "a b" );
  std::streambuf * cin_bak = std::cin.rdbuf( stream.rdbuf() );


  {
    Token &token = lexer.peek();
    CPPUNIT_ASSERT( token.kind == TokenKind::IDENTIFIER );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.column );
    CPPUNIT_ASSERT( token.text == "a" );
    delete &token;
  }

  {
    Token &token = lexer.peek();
    CPPUNIT_ASSERT( token.kind == TokenKind::IDENTIFIER );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.column );
    CPPUNIT_ASSERT( token.text == "a" );
    delete &token;
  }

  {
    Token &token = lexer.get();
    CPPUNIT_ASSERT( token.kind == TokenKind::IDENTIFIER );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.column );
    CPPUNIT_ASSERT( token.text == "a" );
    delete &token;
  }


  {
    Token &token = lexer.peek();
    CPPUNIT_ASSERT( token.kind == TokenKind::IDENTIFIER );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 3u, token.pos.column );
    CPPUNIT_ASSERT( token.text == "b" );
    delete &token;
  }

  {
    Token &token = lexer.peek();
    CPPUNIT_ASSERT( token.kind == TokenKind::IDENTIFIER );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 3u, token.pos.column );
    CPPUNIT_ASSERT( token.text == "b" );
    delete &token;
  }

  {
    Token &token = lexer.get();
    CPPUNIT_ASSERT( token.kind == TokenKind::IDENTIFIER );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 3u, token.pos.column );
    CPPUNIT_ASSERT( token.text == "b" );
    delete &token;
  }

  {
    Token &token = lexer.get();
    CPPUNIT_ASSERT( token.kind == TokenKind::END_OF_FILE );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 4u, token.pos.column );
    delete &token;
  }


  // restode stdin
  std::cin.rdbuf( cin_bak );
}

void LexerTest::testUnget()
{
  Lexer lexer;

  // redirect stdin
  std::istringstream stream( "a b" );
  std::streambuf * cin_bak = std::cin.rdbuf( stream.rdbuf() );


  {
    Token &token = lexer.get();
    CPPUNIT_ASSERT( token.kind == TokenKind::IDENTIFIER );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.column );
    CPPUNIT_ASSERT( token.text == "a" );
    delete &token;
  }

  lexer.unget();

  {
    Token &token = lexer.get();
    CPPUNIT_ASSERT( token.kind == TokenKind::IDENTIFIER );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.column );
    CPPUNIT_ASSERT( token.text == "a" );
    delete &token;
  }

  lexer.unget();
  lexer.unget();

  {
    Token &token = lexer.get();
    CPPUNIT_ASSERT( token.kind == TokenKind::IDENTIFIER );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.column );
    CPPUNIT_ASSERT( token.text == "a" );
    delete &token;
  }

  {
    Token &token = lexer.get();
    CPPUNIT_ASSERT( token.kind == TokenKind::IDENTIFIER );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 3u, token.pos.column );
    CPPUNIT_ASSERT( token.text == "b" );
    delete &token;
  }

  lexer.unget();

  {
    Token &token = lexer.get();
    CPPUNIT_ASSERT( token.kind == TokenKind::IDENTIFIER );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 3u, token.pos.column );
    CPPUNIT_ASSERT( token.text == "b" );
    delete &token;
  }

  {
    Token &token = lexer.get();
    CPPUNIT_ASSERT( token.kind == TokenKind::END_OF_FILE );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 4u, token.pos.column );
    delete &token;
  }


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

  // auto
  token = & lexer.readKeywordOrIdentifier();
  CPPUNIT_ASSERT( token->kind  == TokenKind::KEYWORD );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "auto" );
  delete token;
  lexer.skip();

  // break
  token = & lexer.readKeywordOrIdentifier();
  CPPUNIT_ASSERT( token->kind  == TokenKind::KEYWORD );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 6u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "break" );
  delete token;
  lexer.skip();

  // const
  token = & lexer.readKeywordOrIdentifier();
  CPPUNIT_ASSERT( token->kind  == TokenKind::KEYWORD );
  CPPUNIT_ASSERT_EQUAL( 2u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "const" );
  delete token;
  lexer.skip();

  // int
  token = & lexer.readKeywordOrIdentifier();
  CPPUNIT_ASSERT( token->kind  == TokenKind::KEYWORD );
  CPPUNIT_ASSERT_EQUAL( 3u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 2u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "int" );
  delete token;
  lexer.skip();

  // continue
  token = & lexer.readKeywordOrIdentifier();
  CPPUNIT_ASSERT( token->kind  == TokenKind::KEYWORD );
  CPPUNIT_ASSERT_EQUAL( 4u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "continue" );
  delete token;
  lexer.skip();

  // while
  token = & lexer.readKeywordOrIdentifier();
  CPPUNIT_ASSERT( token->kind  == TokenKind::KEYWORD );
  CPPUNIT_ASSERT_EQUAL( 4u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 10u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "while" );
  delete token;
  lexer.skip();

  // for
  token = & lexer.readKeywordOrIdentifier();
  CPPUNIT_ASSERT( token->kind  == TokenKind::KEYWORD );
  CPPUNIT_ASSERT_EQUAL( 4u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 16u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "for" );
  delete token;
  lexer.skip();


  // restode stdin
  std::cin.rdbuf( cin_bak );
}

void LexerTest::testReadDecimalConstant()
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

void LexerTest::testReadOctalConstant()
{
  std::istringstream stream( "0 01\n023 \n 04 05" );

  // redirect stdin
  std::streambuf * cin_bak = std::cin.rdbuf( stream.rdbuf() );

  Lexer lexer;
  Token * token;

  
  // 0
  token = & lexer.readNumericalConstant();
  CPPUNIT_ASSERT( token->kind  == TokenKind::CONSTANT );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "0" );
  delete token;
  lexer.skip();

  // 01
  token = & lexer.readNumericalConstant();
  CPPUNIT_ASSERT( token->kind  == TokenKind::CONSTANT );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 3u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "01" );
  delete token;
  lexer.skip();

  // 023
  token = & lexer.readNumericalConstant();
  CPPUNIT_ASSERT( token->kind  == TokenKind::CONSTANT );
  CPPUNIT_ASSERT_EQUAL( 2u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "023" );
  delete token;
  lexer.skip();

  // 04
  token = & lexer.readNumericalConstant();
  CPPUNIT_ASSERT( token->kind  == TokenKind::CONSTANT );
  CPPUNIT_ASSERT_EQUAL( 3u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 2u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "04" );
  delete token;
  lexer.skip();

  // 05
  token = & lexer.readNumericalConstant();
  CPPUNIT_ASSERT( token->kind  == TokenKind::CONSTANT );
  CPPUNIT_ASSERT_EQUAL( 3u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 5u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "05" );
  delete token;
  lexer.skip();

  // restode stdin
  std::cin.rdbuf( cin_bak );
}

void LexerTest::testReadHexConstant()
{
  std::istringstream stream( "0x0 0x01\n0xF3 \n 0X2d 0xAa" );

  // redirect stdin
  std::streambuf * cin_bak = std::cin.rdbuf( stream.rdbuf() );

  Lexer lexer;
  Token * token;

  
  // 0x0
  token = & lexer.readNumericalConstant();
  CPPUNIT_ASSERT( token->kind  == TokenKind::CONSTANT );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "0x0" );
  delete token;
  lexer.skip();

  // 0x01
  token = & lexer.readNumericalConstant();
  CPPUNIT_ASSERT( token->kind  == TokenKind::CONSTANT );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 5u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "0x01" );
  delete token;
  lexer.skip();

  // 0xF3
  token = & lexer.readNumericalConstant();
  CPPUNIT_ASSERT( token->kind  == TokenKind::CONSTANT );
  CPPUNIT_ASSERT_EQUAL( 2u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "0xF3" );
  delete token;
  lexer.skip();

  // 0X2d
  token = & lexer.readNumericalConstant();
  CPPUNIT_ASSERT( token->kind  == TokenKind::CONSTANT );
  CPPUNIT_ASSERT_EQUAL( 3u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 2u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "0X2d" );
  delete token;
  lexer.skip();

  // 0xAa
  token = & lexer.readNumericalConstant();
  CPPUNIT_ASSERT( token->kind  == TokenKind::CONSTANT );
  CPPUNIT_ASSERT_EQUAL( 3u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 7u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "0xAa" );
  delete token;
  lexer.skip();


  // restode stdin
  std::cin.rdbuf( cin_bak );
}

void LexerTest::testReadNumericalAndIdentifier()
{
  Lexer lexer;

  // redirect stdin
  std::istringstream stream( "12a 1_ 123uvw 123llux" );
	std::streambuf * cin_bak = std::cin.rdbuf( stream.rdbuf() );


	// 12
  {
    Token &token = lexer.get();
    CPPUNIT_ASSERT( token.kind  == TokenKind::CONSTANT );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.column );
    CPPUNIT_ASSERT( token.text == "12" );
    delete &token;
  }

	// a
  {
    Token &token = lexer.get();
    CPPUNIT_ASSERT( token.kind  == TokenKind::IDENTIFIER );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 3u, token.pos.column );
    CPPUNIT_ASSERT( token.text == "a" );
    delete &token;
  }

	// 1
  {
    Token &token = lexer.get();
    CPPUNIT_ASSERT( token.kind  == TokenKind::CONSTANT );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 5u, token.pos.column );
    CPPUNIT_ASSERT( token.text == "1" );
    delete &token;
  }

	// _
  {
    Token &token = lexer.get();
    CPPUNIT_ASSERT( token.kind  == TokenKind::IDENTIFIER );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 6u, token.pos.column );
    CPPUNIT_ASSERT( token.text == "_" );
    delete &token;
  }

	// 123u
  {
    Token &token = lexer.get();
    CPPUNIT_ASSERT( token.kind  == TokenKind::CONSTANT );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 8u, token.pos.column );
    CPPUNIT_ASSERT( token.text == "123u" );
    delete &token;
  }

	// vw
  {
    Token &token = lexer.get();
    CPPUNIT_ASSERT( token.kind  == TokenKind::IDENTIFIER );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 12u, token.pos.column );
    CPPUNIT_ASSERT( token.text == "vw" );
    delete &token;
  }

	// 123llu
  {
    Token &token = lexer.get();
    CPPUNIT_ASSERT( token.kind  == TokenKind::CONSTANT );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 15u, token.pos.column );
    CPPUNIT_ASSERT( token.text == "123llu" );
    delete &token;
  }

	// x
  {
    Token &token = lexer.get();
    CPPUNIT_ASSERT( token.kind  == TokenKind::IDENTIFIER );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 21u, token.pos.column );
    CPPUNIT_ASSERT( token.text == "x" );
    delete &token;
  }


  // restode stdin
  std::cin.rdbuf( cin_bak );
}

void LexerTest::testReadIntegerSuffix()
{
  std::istringstream stream( "0L 1u 2ll 3uL 4lU" );

  // redirect stdin
  std::streambuf * cin_bak = std::cin.rdbuf( stream.rdbuf() );

  Lexer lexer;
  Token * token;


  // 0L
  token = & lexer.readNumericalConstant();
  CPPUNIT_ASSERT( token->kind  == TokenKind::CONSTANT );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "0L" );
  delete token;
  lexer.skip();

  // 1u
  token = & lexer.readNumericalConstant();
  CPPUNIT_ASSERT( token->kind  == TokenKind::CONSTANT );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 4u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "1u" );
  delete token;
  lexer.skip();

  // 2ll
  token = & lexer.readNumericalConstant();
  CPPUNIT_ASSERT( token->kind  == TokenKind::CONSTANT );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 7u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "2ll" );
  delete token;
  lexer.skip();

  // 3uL
  token = & lexer.readNumericalConstant();
  CPPUNIT_ASSERT( token->kind  == TokenKind::CONSTANT );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 11u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "3uL" );
  delete token;
  lexer.skip();

  // 4lU
  token = & lexer.readNumericalConstant();
  CPPUNIT_ASSERT( token->kind  == TokenKind::CONSTANT );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 15u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "4lU" );
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

void LexerTest::testCharPrefix()
{
  Lexer lexer;

  // redirect stdin
  std::istringstream stream( "L'a'\nu'a'\nU'a'" );
  std::streambuf * cin_bak = std::cin.rdbuf( stream.rdbuf() );


  // L'a'
  {
    Token &token = lexer.readCharacterConstantOrStringLiteral();
    CPPUNIT_ASSERT( token.kind  == TokenKind::CONSTANT );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.column );
    CPPUNIT_ASSERT( token.text == "L'a'" );
    delete &token;
  }
  lexer.skip();

  // u'a'
  {
    Token &token = lexer.readCharacterConstantOrStringLiteral();
    CPPUNIT_ASSERT( token.kind  == TokenKind::CONSTANT );
    CPPUNIT_ASSERT_EQUAL( 2u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.column );
    CPPUNIT_ASSERT( token.text == "u'a'" );
    delete &token;
  }
  lexer.skip();

  // U'a'
  {
    Token &token = lexer.readCharacterConstantOrStringLiteral();
    CPPUNIT_ASSERT( token.kind  == TokenKind::CONSTANT );
    CPPUNIT_ASSERT_EQUAL( 3u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.column );
    CPPUNIT_ASSERT( token.text == "U'a'" );
    delete &token;
  }

  // restode stdin
  std::cin.rdbuf( cin_bak );
}

void LexerTest::testReadStringLiteral()
{
  Lexer lexer;

  // redirect stdin
  std::istringstream stream( "\"a\" \n \"bc\"\r\n\"d e \" \"\\n bla\"" );
  std::streambuf * cin_bak = std::cin.rdbuf( stream.rdbuf() );

  Token * token;

  // "a"
  token = & lexer.readCharacterConstantOrStringLiteral();
  CPPUNIT_ASSERT( token->kind  == TokenKind::STRING_LITERAL );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "\"a\"" );
  delete token;
  lexer.skip();

  // "bc"
  token = & lexer.readCharacterConstantOrStringLiteral();
  CPPUNIT_ASSERT( token->kind  == TokenKind::STRING_LITERAL );
  CPPUNIT_ASSERT_EQUAL( 2u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 2u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "\"bc\"" );
  delete token;
  lexer.skip();

  // "d e "
  token = & lexer.readCharacterConstantOrStringLiteral();
  CPPUNIT_ASSERT( token->kind  == TokenKind::STRING_LITERAL );
  CPPUNIT_ASSERT_EQUAL( 3u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "\"d e \"" );
  delete token;
  lexer.skip();

  // "\n bla"
  token = & lexer.readCharacterConstantOrStringLiteral();
  CPPUNIT_ASSERT( token->kind  == TokenKind::STRING_LITERAL );
  CPPUNIT_ASSERT_EQUAL( 3u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 8u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "\"\\n bla\"" );
  delete token;
  lexer.skip();


  stream.str( "\n\"\"" );
  std::cin.rdbuf( stream.rdbuf() );
  
  lexer.skip();

  token = & lexer.readCharacterConstantOrStringLiteral();
  CPPUNIT_ASSERT( token->kind  == TokenKind::STRING_LITERAL );
  CPPUNIT_ASSERT_EQUAL( 4u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "\"\"" );
  delete token;


  // restode stdin
  std::cin.rdbuf( cin_bak );
}

void LexerTest::testReadPunctuator()
{
  std::istringstream stream( "[->>>=....|||--=" );

  // redirect stdin
  std::streambuf * cin_bak = std::cin.rdbuf( stream.rdbuf() );

  Lexer lexer;
  Token * token;

  // [
  token = & lexer.readPunctuator();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "[" );
  delete token;
  lexer.skip();

  // ->
  token = & lexer.readPunctuator();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 2u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "->" );
  delete token;
  lexer.skip();

  // >>=
  token = & lexer.readPunctuator();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 4u, token->pos.column );
  CPPUNIT_ASSERT( token->text == ">>=" );
  delete token;
  lexer.skip();

  // ...
  token = & lexer.readPunctuator();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 7u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "..." );
  delete token;
  lexer.skip();

  // .
  token = & lexer.readPunctuator();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 10u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "." );
  delete token;
  lexer.skip();

  // ||
  token = & lexer.readPunctuator();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 11u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "||" );
  delete token;
  lexer.skip();

  // |
  token = & lexer.readPunctuator();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 13u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "|" );
  delete token;
  lexer.skip();

  // --
  token = & lexer.readPunctuator();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 14u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "--" );
  delete token;
  lexer.skip();

  // =
  token = & lexer.readPunctuator();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 16u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "=" );
  delete token;
  lexer.skip();


  // restode stdin
  std::cin.rdbuf( cin_bak );
}

void LexerTest::testReadPunctuatorDigraph()
{
  std::istringstream stream( "<::><%%>%: %:%:" );

  // redirect stdin
  std::streambuf * cin_bak = std::cin.rdbuf( stream.rdbuf() );

  Lexer lexer;
  Token * token;


  // <:
  token = & lexer.readPunctuator();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "<:" );
  delete token;
  lexer.skip();

  // :>
  token = & lexer.readPunctuator();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 3u, token->pos.column );
  CPPUNIT_ASSERT( token->text == ":>" );
  delete token;
  lexer.skip();

  // <%
  token = & lexer.readPunctuator();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 5u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "<%" );
  delete token;
  lexer.skip();

  // %>
  token = & lexer.readPunctuator();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 7u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "%>" );
  delete token;
  lexer.skip();

  // %:
  token = & lexer.readPunctuator();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 9u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "%:" );
  delete token;
  lexer.skip();

  // %:%:
  token = & lexer.readPunctuator();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 12u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "%:%:" );
  delete token;
  lexer.skip();


  // restode stdin
  std::cin.rdbuf( cin_bak );
}

void LexerTest::testHelloWorld()
{
  // #include <stdio>
  // int main()
  // {
  //  printf( "Hello World!\n" );
  //  return 0;
  // }
  std::istringstream stream( "\
#include <stdio.h>\n\
\n\
int main()\n\
{\n\
  printf( \"Hello World!\\n\" );\n\
  return 0;\n\
}" );

  // redirect stdin
  std::streambuf * cin_bak = std::cin.rdbuf( stream.rdbuf() );

  Lexer lexer;
  Token * token;

  // #
  token = & lexer.get();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "#" );
  delete token;

  // include
  token = & lexer.get();
  CPPUNIT_ASSERT( token->kind  == TokenKind::IDENTIFIER );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 2u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "include" );
  delete token;

  // <
  token = & lexer.get();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 10u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "<" );
  delete token;

  // stdio
  token = & lexer.get();
  CPPUNIT_ASSERT( token->kind  == TokenKind::IDENTIFIER );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 11u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "stdio" );
  delete token;

  // .
  token = & lexer.get();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 16u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "." );
  delete token;

  // h
  token = & lexer.get();
  CPPUNIT_ASSERT( token->kind  == TokenKind::IDENTIFIER );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 17u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "h" );
  delete token;

  // >
  token = & lexer.get();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 18u, token->pos.column );
  CPPUNIT_ASSERT( token->text == ">" );
  delete token;

  // int
  token = & lexer.get();
  CPPUNIT_ASSERT( token->kind  == TokenKind::KEYWORD );
  CPPUNIT_ASSERT_EQUAL( 3u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "int" );
  delete token;

  // main
  token = & lexer.get();
  CPPUNIT_ASSERT( token->kind  == TokenKind::IDENTIFIER );
  CPPUNIT_ASSERT_EQUAL( 3u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 5u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "main" );
  delete token;

  // (
  token = & lexer.get();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 3u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 9u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "(" );
  delete token;

  // )
  token = & lexer.get();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 3u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 10u, token->pos.column );
  CPPUNIT_ASSERT( token->text == ")" );
  delete token;

  // {
  token = & lexer.get();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 4u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "{" );
  delete token;

  // printf
  token = & lexer.get();
  CPPUNIT_ASSERT( token->kind  == TokenKind::IDENTIFIER );
  CPPUNIT_ASSERT_EQUAL( 5u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 3u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "printf" );
  delete token;

  // (
  token = & lexer.get();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 5u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 9u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "(" );
  delete token;

  // "Hello World!\n"
  token = & lexer.get();
  CPPUNIT_ASSERT( token->kind  == TokenKind::STRING_LITERAL );
  CPPUNIT_ASSERT_EQUAL( 5u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 11u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "\"Hello World!\\n\"" );
  delete token;

  // )
  token = & lexer.get();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 5u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 28u, token->pos.column );
  CPPUNIT_ASSERT( token->text == ")" );
  delete token;

  // ;
  token = & lexer.get();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 5u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 29u, token->pos.column );
  CPPUNIT_ASSERT( token->text == ";" );
  delete token;

  // return
  token = & lexer.get();
  CPPUNIT_ASSERT( token->kind  == TokenKind::KEYWORD );
  CPPUNIT_ASSERT_EQUAL( 6u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 3u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "return" );
  delete token;

  // 0
  token = & lexer.get();
  CPPUNIT_ASSERT( token->kind  == TokenKind::CONSTANT );
  CPPUNIT_ASSERT_EQUAL( 6u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 10u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "0" );
  delete token;

  // ;
  token = & lexer.get();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 6u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 11u, token->pos.column );
  CPPUNIT_ASSERT( token->text == ";" );
  delete token;

  // }
  token = & lexer.get();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 7u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "}" );
  delete token;


  // restode stdin
  std::cin.rdbuf( cin_bak );
}

void LexerTest::testReadPunctuatorDots()
{
  // redirect stdin
  std::istringstream stream( "........" );
  std::streambuf * cin_bak = std::cin.rdbuf( stream.rdbuf() );

  Lexer lexer;
  Token * token;

  // ...
  token = & lexer.get();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "..." );
  delete token;

  // ...
  token = & lexer.get();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 4u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "..." );
  delete token;

  // .
  token = & lexer.get();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 7u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "." );
  delete token;

  // .
  token = & lexer.get();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 8u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "." );
  delete token;

  
  // restode stdin
  std::cin.rdbuf( cin_bak );
}

void LexerTest::testReadPunctuatorDigraphAmbiguity()
{
  // redirect stdin
  std::istringstream stream( "<:>" );
  std::streambuf * cin_bak = std::cin.rdbuf( stream.rdbuf() );

  Lexer lexer;
  Token * token;

  // <:
  token = & lexer.get();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "<:" );
  delete token;

  // >
  token = & lexer.get();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 3u, token->pos.column );
  CPPUNIT_ASSERT( token->text == ">" );
  delete token;


  // redirect stdin
  stream.str( "\n<%>" );
  std::cin.rdbuf( stream.rdbuf() );
  
  // <%
  token = & lexer.get();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 2u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "<%" );
  delete token;

  // >
  token = & lexer.get();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 2u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 3u, token->pos.column );
  CPPUNIT_ASSERT( token->text == ">" );
  delete token;


  // redirect stdin
  stream.str( "\n%:%:%:%" );
  std::cin.rdbuf( stream.rdbuf() );
  
  // %:%:
  token = & lexer.get();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 3u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "%:%:" );
  delete token;

  // %:
  token = & lexer.get();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 3u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 5u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "%:" );
  delete token;

  // %
  token = & lexer.get();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 3u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 7u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "%" );
  delete token;


  // redirect stdin
  stream.str( "\n<%:>" );
  std::cin.rdbuf( stream.rdbuf() );
  
  // <%
  token = & lexer.get();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 4u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "<%" );
  delete token;

  // :>
  token = & lexer.get();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 4u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 3u, token->pos.column );
  CPPUNIT_ASSERT( token->text == ":>" );
  delete token;


  // redirect stdin
  stream.str( "\n<<::>>" );
  std::cin.rdbuf( stream.rdbuf() );
  
  // <<
  token = & lexer.get();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 5u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "<<" );
  delete token;

  // :
  token = & lexer.get();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 5u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 3u, token->pos.column );
  CPPUNIT_ASSERT( token->text == ":" );
  delete token;

  // :>
  token = & lexer.get();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 5u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 4u, token->pos.column );
  CPPUNIT_ASSERT( token->text == ":>" );
  delete token;

  // >
  token = & lexer.get();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 5u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 6u, token->pos.column );
  CPPUNIT_ASSERT( token->text == ">" );
  delete token;


  // restode stdin
  std::cin.rdbuf( cin_bak );
}

void LexerTest::testComments()
{
  // redirect stdin
  std::istringstream stream( "//" );
  std::streambuf * cin_bak = std::cin.rdbuf( stream.rdbuf() );

  Lexer lexer;
  Token * token;


  token = & lexer.get();
  CPPUNIT_ASSERT( token->kind == TokenKind::END_OF_FILE );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 3u, token->pos.column );
  delete token;


  // redirect stdin
  stream.str( "\n//\\\n" );
  std::cin.rdbuf( stream.rdbuf() );

  token = & lexer.get();
  CPPUNIT_ASSERT( token->kind == TokenKind::END_OF_FILE );
  CPPUNIT_ASSERT_EQUAL( 3u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.column );
  delete token;


  // redirect stdin
  stream.str( "\n/**/" );
  std::cin.rdbuf( stream.rdbuf() );

  token = & lexer.get();
  CPPUNIT_ASSERT( token->kind == TokenKind::END_OF_FILE );
  CPPUNIT_ASSERT_EQUAL( 4u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 5u, token->pos.column );
  delete token;


  // redirect stdin
  stream.str( "\n/*\n\\\n*/" );
  std::cin.rdbuf( stream.rdbuf() );

  token = & lexer.get();
  CPPUNIT_ASSERT( token->kind == TokenKind::END_OF_FILE );
  CPPUNIT_ASSERT_EQUAL( 7u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 3u, token->pos.column );
  delete token;


  // redirect stdin
  stream.str( "\n//*" );
  std::cin.rdbuf( stream.rdbuf() );

  token = & lexer.get();
  CPPUNIT_ASSERT( token->kind == TokenKind::END_OF_FILE );
  CPPUNIT_ASSERT_EQUAL( 8u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 4u, token->pos.column );
  delete token;


  // redirect stdin
  stream.str( "\n///*" );
  std::cin.rdbuf( stream.rdbuf() );

  token = & lexer.get();
  CPPUNIT_ASSERT( token->kind == TokenKind::END_OF_FILE );
  CPPUNIT_ASSERT_EQUAL( 9u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 5u, token->pos.column );
  delete token;


  // redirect stdin
  stream.str( "\nint /*This is a multi-line\ncomment*/a = TEN;" );
  std::cin.rdbuf( stream.rdbuf() );

  token = & lexer.get();
  CPPUNIT_ASSERT( token->kind == TokenKind::KEYWORD );
  CPPUNIT_ASSERT_EQUAL( 10u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "int" );
  delete token;

  token = & lexer.get();
  CPPUNIT_ASSERT( token->kind == TokenKind::IDENTIFIER );
  CPPUNIT_ASSERT_EQUAL( 11u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 10u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "a" );
  delete token;

  token = & lexer.get();
  CPPUNIT_ASSERT( token->kind == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 11u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 12u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "=" );
  delete token;

  token = & lexer.get();
  CPPUNIT_ASSERT( token->kind == TokenKind::IDENTIFIER );
  CPPUNIT_ASSERT_EQUAL( 11u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 14u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "TEN" );
  delete token;


  // restode stdin
  std::cin.rdbuf( cin_bak );
}

void LexerTest::testReadCommentAsWhitespace()
{
  Lexer lexer;

  // redirect stdin
  std::istringstream stream( "abc/**/def" );
  std::streambuf * cin_bak = std::cin.rdbuf( stream.rdbuf() );


  // abc
  {
    Token &token = lexer.get();
    CPPUNIT_ASSERT( token.kind == TokenKind::IDENTIFIER );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.column );
    CPPUNIT_ASSERT( token.text == "abc" );
    delete &token;
  }

  // def
  {
    Token &token = lexer.get();
    CPPUNIT_ASSERT( token.kind == TokenKind::IDENTIFIER );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 8u, token.pos.column );
    CPPUNIT_ASSERT( token.text == "def" );
    delete &token;
  }


  // redirect stdin
  stream.str( "\nau/**/to" );
  std::cin.rdbuf( stream.rdbuf() );


  // au
  {
    Token &token = lexer.get();
    CPPUNIT_ASSERT( token.kind == TokenKind::IDENTIFIER );
    CPPUNIT_ASSERT_EQUAL( 2u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.column );
    CPPUNIT_ASSERT( token.text == "au" );
    delete &token;
  }

  // to
  {
    Token &token = lexer.get();
    CPPUNIT_ASSERT( token.kind == TokenKind::IDENTIFIER );
    CPPUNIT_ASSERT_EQUAL( 2u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 7u, token.pos.column );
    CPPUNIT_ASSERT( token.text == "to" );
    delete &token;
  }


  // redirect stdin
  stream.str( "\n123/**/456" );
  std::cin.rdbuf( stream.rdbuf() );


  // 123
  {
    Token &token = lexer.get();
    CPPUNIT_ASSERT( token.kind == TokenKind::CONSTANT );
    CPPUNIT_ASSERT_EQUAL( 3u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.column );
    CPPUNIT_ASSERT( token.text == "123" );
    delete &token;
  }

  // 456
  {
    Token &token = lexer.get();
    CPPUNIT_ASSERT( token.kind == TokenKind::CONSTANT );
    CPPUNIT_ASSERT_EQUAL( 3u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 8u, token.pos.column );
    CPPUNIT_ASSERT( token.text == "456" );
    delete &token;
  }


  // redirect stdin
  stream.str( "\n</**/<=" );
  std::cin.rdbuf( stream.rdbuf() );


  // <
  {
    Token &token = lexer.get();
    CPPUNIT_ASSERT( token.kind == TokenKind::PUNCTUATOR );
    CPPUNIT_ASSERT_EQUAL( 4u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.column );
    CPPUNIT_ASSERT( token.text == "<" );
    delete &token;
  }

  // <=
  {
    Token &token = lexer.get();
    CPPUNIT_ASSERT( token.kind == TokenKind::PUNCTUATOR );
    CPPUNIT_ASSERT_EQUAL( 4u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 6u, token.pos.column );
    CPPUNIT_ASSERT( token.text == "<=" );
    delete &token;
  }


  // restode stdin
  std::cin.rdbuf( cin_bak );
}
