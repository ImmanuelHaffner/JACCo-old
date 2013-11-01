//===--- LexerTest.cc -----------------------------------------------------===//
//
//	~~~ The C4 Compiler TestSuite ~~~
//
//===----------------------------------------------------------------------===//

#include "LexerTest.h"

#include "../src/Lex/Lexer.h"
#include "../src/Lex/KeywordToken.h"
#include "../src/Lex/PunctuatorToken.h"
#include "../src/Lex/IllegalToken.h"


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
  keyword = static_cast< KeywordToken* >( token );
  CPPUNIT_ASSERT( keyword->keyword == KeywordKind::AUTO );
  delete token;
  lexer.skip();

  // break
  token = & lexer.readKeywordOrIdentifier();
  CPPUNIT_ASSERT( token->kind  == TokenKind::KEYWORD );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 6u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "break" );
  keyword = static_cast< KeywordToken* >( token );
  CPPUNIT_ASSERT( keyword->keyword == KeywordKind::BREAK );
  delete token;
  lexer.skip();

  // const
  token = & lexer.readKeywordOrIdentifier();
  CPPUNIT_ASSERT( token->kind  == TokenKind::KEYWORD );
  CPPUNIT_ASSERT_EQUAL( 2u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "const" );
  keyword = static_cast< KeywordToken* >( token );
  CPPUNIT_ASSERT( keyword->keyword == KeywordKind::CONST );
  delete token;
  lexer.skip();

  // int
  token = & lexer.readKeywordOrIdentifier();
  CPPUNIT_ASSERT( token->kind  == TokenKind::KEYWORD );
  CPPUNIT_ASSERT_EQUAL( 3u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 2u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "int" );
  keyword = static_cast< KeywordToken* >( token );
  CPPUNIT_ASSERT( keyword->keyword == KeywordKind::INT );
  delete token;
  lexer.skip();

  // continue
  token = & lexer.readKeywordOrIdentifier();
  CPPUNIT_ASSERT( token->kind  == TokenKind::KEYWORD );
  CPPUNIT_ASSERT_EQUAL( 4u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "continue" );
  keyword = static_cast< KeywordToken* >( token );
  CPPUNIT_ASSERT( keyword->keyword == KeywordKind::CONTINUE );
  delete token;
  lexer.skip();

  // while
  token = & lexer.readKeywordOrIdentifier();
  CPPUNIT_ASSERT( token->kind  == TokenKind::KEYWORD );
  CPPUNIT_ASSERT_EQUAL( 4u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 10u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "while" );
  keyword = static_cast< KeywordToken* >( token );
  CPPUNIT_ASSERT( keyword->keyword == KeywordKind::WHILE );
  delete token;
  lexer.skip();

  // for
  token = & lexer.readKeywordOrIdentifier();
  CPPUNIT_ASSERT( token->kind  == TokenKind::KEYWORD );
  CPPUNIT_ASSERT_EQUAL( 4u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 16u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "for" );
  keyword = static_cast< KeywordToken* >( token );
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

void LexerTest::testReadStringLiteral()
{
  std::istringstream stream( "\"a\" \n \"bc\"\r\n\"d e \" \"\\n bla\"" );

  // redirect stdin
  std::streambuf * cin_bak = std::cin.rdbuf( stream.rdbuf() );

  Lexer lexer;
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
  PunctuatorToken * punctuator;

  // [
  token = & lexer.readPunctuator();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "[" );
  punctuator = static_cast< PunctuatorToken* >( token );
  CPPUNIT_ASSERT( punctuator->punctuator == PunctuatorKind::LBRACKET );
  delete token;
  lexer.skip();

  // ->
  token = & lexer.readPunctuator();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 2u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "->" );
  punctuator = static_cast< PunctuatorToken* >( token );
  CPPUNIT_ASSERT( punctuator->punctuator == PunctuatorKind::ARROW );
  delete token;
  lexer.skip();

  // >>=
  token = & lexer.readPunctuator();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 4u, token->pos.column );
  CPPUNIT_ASSERT( token->text == ">>=" );
  punctuator = static_cast< PunctuatorToken* >( token );
  CPPUNIT_ASSERT( punctuator->punctuator == PunctuatorKind::RSHIFTASSIGN );
  delete token;
  lexer.skip();

  // ...
  token = & lexer.readPunctuator();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 7u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "..." );
  punctuator = static_cast< PunctuatorToken* >( token );
  CPPUNIT_ASSERT( punctuator->punctuator == PunctuatorKind::LDOTS );
  delete token;
  lexer.skip();

  // .
  token = & lexer.readPunctuator();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 10u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "." );
  punctuator = static_cast< PunctuatorToken* >( token );
  CPPUNIT_ASSERT( punctuator->punctuator == PunctuatorKind::DOT );
  delete token;
  lexer.skip();

  // ||
  token = & lexer.readPunctuator();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 11u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "||" );
  punctuator = static_cast< PunctuatorToken* >( token );
  CPPUNIT_ASSERT( punctuator->punctuator == PunctuatorKind::LOR );
  delete token;
  lexer.skip();

  // |
  token = & lexer.readPunctuator();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 13u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "|" );
  punctuator = static_cast< PunctuatorToken* >( token );
  CPPUNIT_ASSERT( punctuator->punctuator == PunctuatorKind::OR );
  delete token;
  lexer.skip();

  // --
  token = & lexer.readPunctuator();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 14u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "--" );
  punctuator = static_cast< PunctuatorToken* >( token );
  CPPUNIT_ASSERT( punctuator->punctuator == PunctuatorKind::DEC );
  delete token;
  lexer.skip();

  // =
  token = & lexer.readPunctuator();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 16u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "=" );
  punctuator = static_cast< PunctuatorToken* >( token );
  CPPUNIT_ASSERT( punctuator->punctuator == PunctuatorKind::ASSIGN );
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
  PunctuatorToken * punctuator;


  // <:
  token = & lexer.readPunctuator();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "<:" );
  punctuator = static_cast< PunctuatorToken* >( token );
  CPPUNIT_ASSERT( punctuator->punctuator == PunctuatorKind::LBRACKET );
  delete token;
  lexer.skip();

  // :>
  token = & lexer.readPunctuator();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 3u, token->pos.column );
  CPPUNIT_ASSERT( token->text == ":>" );
  punctuator = static_cast< PunctuatorToken* >( token );
  CPPUNIT_ASSERT( punctuator->punctuator == PunctuatorKind::RBRACKET );
  delete token;
  lexer.skip();

  // <%
  token = & lexer.readPunctuator();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 5u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "<%" );
  punctuator = static_cast< PunctuatorToken* >( token );
  CPPUNIT_ASSERT( punctuator->punctuator == PunctuatorKind::LBRACE );
  delete token;
  lexer.skip();

  // %>
  token = & lexer.readPunctuator();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 7u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "%>" );
  punctuator = static_cast< PunctuatorToken* >( token );
  CPPUNIT_ASSERT( punctuator->punctuator == PunctuatorKind::RBRACE );
  delete token;
  lexer.skip();

  // %:
  token = & lexer.readPunctuator();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 9u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "%:" );
  punctuator = static_cast< PunctuatorToken* >( token );
  CPPUNIT_ASSERT( punctuator->punctuator == PunctuatorKind::HASH );
  delete token;
  lexer.skip();

  // %:%:
  token = & lexer.readPunctuator();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 12u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "%:%:" );
  punctuator = static_cast< PunctuatorToken* >( token );
  CPPUNIT_ASSERT( punctuator->punctuator == PunctuatorKind::DHASH );
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
  PunctuatorToken * punctuator;
  KeywordToken * keyword;

  // #
  token = & lexer.getToken();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "#" );
  punctuator = static_cast< PunctuatorToken* >( token );
  CPPUNIT_ASSERT( punctuator->punctuator == PunctuatorKind::HASH );
  delete token;

  // include
  token = & lexer.getToken();
  CPPUNIT_ASSERT( token->kind  == TokenKind::IDENTIFIER );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 2u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "include" );
  delete token;

  // <
  token = & lexer.getToken();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 10u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "<" );
  punctuator = static_cast< PunctuatorToken* >( token );
  CPPUNIT_ASSERT( punctuator->punctuator == PunctuatorKind::LE );
  delete token;

  // stdio
  token = & lexer.getToken();
  CPPUNIT_ASSERT( token->kind  == TokenKind::IDENTIFIER );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 11u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "stdio" );
  delete token;

  // .
  token = & lexer.getToken();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 16u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "." );
  punctuator = static_cast< PunctuatorToken* >( token );
  CPPUNIT_ASSERT( punctuator->punctuator == PunctuatorKind::DOT );
  delete token;

  // h
  token = & lexer.getToken();
  CPPUNIT_ASSERT( token->kind  == TokenKind::IDENTIFIER );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 17u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "h" );
  delete token;

  // >
  token = & lexer.getToken();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 18u, token->pos.column );
  CPPUNIT_ASSERT( token->text == ">" );
  punctuator = static_cast< PunctuatorToken* >( token );
  CPPUNIT_ASSERT( punctuator->punctuator == PunctuatorKind::GR );
  delete token;

  // int
  token = & lexer.getToken();
  CPPUNIT_ASSERT( token->kind  == TokenKind::KEYWORD );
  CPPUNIT_ASSERT_EQUAL( 3u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "int" );
  keyword = static_cast< KeywordToken* >( token );
  CPPUNIT_ASSERT( keyword->keyword == KeywordKind::INT );
  delete token;

  // main
  token = & lexer.getToken();
  CPPUNIT_ASSERT( token->kind  == TokenKind::IDENTIFIER );
  CPPUNIT_ASSERT_EQUAL( 3u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 5u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "main" );
  delete token;

  // (
  token = & lexer.getToken();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 3u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 9u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "(" );
  punctuator = static_cast< PunctuatorToken* >( token );
  CPPUNIT_ASSERT( punctuator->punctuator == PunctuatorKind::LPAR );
  delete token;

  // )
  token = & lexer.getToken();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 3u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 10u, token->pos.column );
  CPPUNIT_ASSERT( token->text == ")" );
  punctuator = static_cast< PunctuatorToken* >( token );
  CPPUNIT_ASSERT( punctuator->punctuator == PunctuatorKind::RPAR );
  delete token;

  // {
  token = & lexer.getToken();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 4u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "{" );
  punctuator = static_cast< PunctuatorToken* >( token );
  CPPUNIT_ASSERT( punctuator->punctuator == PunctuatorKind::LBRACE );
  delete token;

  // printf
  token = & lexer.getToken();
  CPPUNIT_ASSERT( token->kind  == TokenKind::IDENTIFIER );
  CPPUNIT_ASSERT_EQUAL( 5u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 3u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "printf" );
  delete token;

  // (
  token = & lexer.getToken();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 5u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 9u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "(" );
  punctuator = static_cast< PunctuatorToken* >( token );
  CPPUNIT_ASSERT( punctuator->punctuator == PunctuatorKind::LPAR );
  delete token;

  // "Hello World!\n"
  token = & lexer.getToken();
  CPPUNIT_ASSERT( token->kind  == TokenKind::STRING_LITERAL );
  CPPUNIT_ASSERT_EQUAL( 5u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 11u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "\"Hello World!\\n\"" );
  delete token;

  // )
  token = & lexer.getToken();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 5u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 28u, token->pos.column );
  CPPUNIT_ASSERT( token->text == ")" );
  punctuator = static_cast< PunctuatorToken* >( token );
  CPPUNIT_ASSERT( punctuator->punctuator == PunctuatorKind::RPAR );
  delete token;

  // ;
  token = & lexer.getToken();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 5u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 29u, token->pos.column );
  CPPUNIT_ASSERT( token->text == ";" );
  punctuator = static_cast< PunctuatorToken* >( token );
  CPPUNIT_ASSERT( punctuator->punctuator == PunctuatorKind::SEMICOLON );
  delete token;

  // return
  token = & lexer.getToken();
  CPPUNIT_ASSERT( token->kind  == TokenKind::KEYWORD );
  CPPUNIT_ASSERT_EQUAL( 6u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 3u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "return" );
  keyword = static_cast< KeywordToken* >( token );
  CPPUNIT_ASSERT( keyword->keyword == KeywordKind::RETURN );
  delete token;

  // 0
  token = & lexer.getToken();
  CPPUNIT_ASSERT( token->kind  == TokenKind::CONSTANT );
  CPPUNIT_ASSERT_EQUAL( 6u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 10u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "0" );
  delete token;

  // ;
  token = & lexer.getToken();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 6u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 11u, token->pos.column );
  CPPUNIT_ASSERT( token->text == ";" );
  punctuator = static_cast< PunctuatorToken* >( token );
  CPPUNIT_ASSERT( punctuator->punctuator == PunctuatorKind::SEMICOLON );
  delete token;

  // }
  token = & lexer.getToken();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 7u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "}" );
  punctuator = static_cast< PunctuatorToken* >( token );
  CPPUNIT_ASSERT( punctuator->punctuator == PunctuatorKind::RBRACE );
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
  PunctuatorToken * punctuator;

  // ...
  token = & lexer.getToken();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "..." );
  punctuator = static_cast< PunctuatorToken* >( token );
  CPPUNIT_ASSERT( punctuator->punctuator == PunctuatorKind::LDOTS );
  delete token;

  // ...
  token = & lexer.getToken();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 4u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "..." );
  punctuator = static_cast< PunctuatorToken* >( token );
  CPPUNIT_ASSERT( punctuator->punctuator == PunctuatorKind::LDOTS );
  delete token;

  // .
  token = & lexer.getToken();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 7u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "." );
  punctuator = static_cast< PunctuatorToken* >( token );
  CPPUNIT_ASSERT( punctuator->punctuator == PunctuatorKind::DOT );
  delete token;

  // .
  token = & lexer.getToken();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 8u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "." );
  punctuator = static_cast< PunctuatorToken* >( token );
  CPPUNIT_ASSERT( punctuator->punctuator == PunctuatorKind::DOT );
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
  PunctuatorToken * punctuator;

  // <:
  token = & lexer.getToken();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "<:" );
  punctuator = static_cast< PunctuatorToken* >( token );
  CPPUNIT_ASSERT( punctuator->punctuator == PunctuatorKind::LBRACKET );
  delete token;

  // >
  token = & lexer.getToken();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 3u, token->pos.column );
  CPPUNIT_ASSERT( token->text == ">" );
  punctuator = static_cast< PunctuatorToken* >( token );
  CPPUNIT_ASSERT( punctuator->punctuator == PunctuatorKind::GR );
  delete token;


  // redirect stdin
  stream.str( "\n<%>" );
  std::cin.rdbuf( stream.rdbuf() );
  
  // <%
  token = & lexer.getToken();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 2u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "<%" );
  punctuator = static_cast< PunctuatorToken* >( token );
  CPPUNIT_ASSERT( punctuator->punctuator == PunctuatorKind::LBRACE );
  delete token;

  // >
  token = & lexer.getToken();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 2u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 3u, token->pos.column );
  CPPUNIT_ASSERT( token->text == ">" );
  punctuator = static_cast< PunctuatorToken* >( token );
  CPPUNIT_ASSERT( punctuator->punctuator == PunctuatorKind::GR );
  delete token;


  // redirect stdin
  stream.str( "\n%:%:%:" );
  std::cin.rdbuf( stream.rdbuf() );
  
  // %:%:
  token = & lexer.getToken();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 3u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "%:%:" );
  punctuator = static_cast< PunctuatorToken* >( token );
  CPPUNIT_ASSERT( punctuator->punctuator == PunctuatorKind::DHASH );
  delete token;

  // %:
  token = & lexer.getToken();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 3u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 5u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "%:" );
  punctuator = static_cast< PunctuatorToken* >( token );
  CPPUNIT_ASSERT( punctuator->punctuator == PunctuatorKind::HASH );
  delete token;


  // redirect stdin
  stream.str( "\n<%:>" );
  std::cin.rdbuf( stream.rdbuf() );
  
  // <%
  token = & lexer.getToken();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 4u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "<%" );
  punctuator = static_cast< PunctuatorToken* >( token );
  CPPUNIT_ASSERT( punctuator->punctuator == PunctuatorKind::LBRACE );
  delete token;

  // :>
  token = & lexer.getToken();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 4u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 3u, token->pos.column );
  CPPUNIT_ASSERT( token->text == ":>" );
  punctuator = static_cast< PunctuatorToken* >( token );
  CPPUNIT_ASSERT( punctuator->punctuator == PunctuatorKind::RBRACKET );
  delete token;


  // redirect stdin
  stream.str( "\n<<::>>" );
  std::cin.rdbuf( stream.rdbuf() );
  
  // <<
  token = & lexer.getToken();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 5u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "<<" );
  punctuator = static_cast< PunctuatorToken* >( token );
  CPPUNIT_ASSERT( punctuator->punctuator == PunctuatorKind::LSHIFT );
  delete token;

  // :
  token = & lexer.getToken();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 5u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 3u, token->pos.column );
  CPPUNIT_ASSERT( token->text == ":" );
  punctuator = static_cast< PunctuatorToken* >( token );
  CPPUNIT_ASSERT( punctuator->punctuator == PunctuatorKind::COLON );
  delete token;

  // :>
  token = & lexer.getToken();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 5u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 4u, token->pos.column );
  CPPUNIT_ASSERT( token->text == ":>" );
  punctuator = static_cast< PunctuatorToken* >( token );
  CPPUNIT_ASSERT( punctuator->punctuator == PunctuatorKind::RBRACKET );
  delete token;

  // >
  token = & lexer.getToken();
  CPPUNIT_ASSERT( token->kind  == TokenKind::PUNCTUATOR );
  CPPUNIT_ASSERT_EQUAL( 5u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 6u, token->pos.column );
  CPPUNIT_ASSERT( token->text == ">" );
  punctuator = static_cast< PunctuatorToken* >( token );
  CPPUNIT_ASSERT( punctuator->punctuator == PunctuatorKind::GR );
  delete token;


  // restode stdin
  std::cin.rdbuf( cin_bak );
}

void LexerTest::testEmptyCharConst()
{
  // redirect stdin
  std::istringstream stream( "''''" );
  std::streambuf * cin_bak = std::cin.rdbuf( stream.rdbuf() );

  Lexer lexer;
  Token * token;
  IllegalToken * itok;


	// ''
  token = & lexer.getToken();
  CPPUNIT_ASSERT( token->kind  == TokenKind::ILLEGAL );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "''" );
  itok = static_cast< IllegalToken* >( token );
  CPPUNIT_ASSERT( itok->iKind == IllegalTokenKind::EMPTY_CHARACTER_CONSTANT );
  delete token;

	// ''
  token = & lexer.getToken();
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

void LexerTest::testIllegalIdentifiers()
{
  // redirect stdin
  std::istringstream stream( "12a 1_ 1_2 1a2" );
	std::streambuf * cin_bak = std::cin.rdbuf( stream.rdbuf() );

  Lexer lexer;
  Token * token;
  IllegalToken * itok;


	// 12a
  token = & lexer.getToken();
  CPPUNIT_ASSERT( token->kind  == TokenKind::ILLEGAL );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "12a" );
  itok = static_cast< IllegalToken* >( token );
  CPPUNIT_ASSERT( itok->iKind == IllegalTokenKind::IDENTIFIER );
  delete token;

	// 1_
  token = & lexer.getToken();
  CPPUNIT_ASSERT( token->kind  == TokenKind::ILLEGAL );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 5u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "1_" );
  itok = static_cast< IllegalToken* >( token );
  CPPUNIT_ASSERT( itok->iKind == IllegalTokenKind::IDENTIFIER );
  delete token;

	// 1_2
  token = & lexer.getToken();
  CPPUNIT_ASSERT( token->kind  == TokenKind::ILLEGAL );
  CPPUNIT_ASSERT_EQUAL( 1u, token->pos.line );
  CPPUNIT_ASSERT_EQUAL( 8u, token->pos.column );
  CPPUNIT_ASSERT( token->text == "1_2" );
  itok = static_cast< IllegalToken* >( token );
  CPPUNIT_ASSERT( itok->iKind == IllegalTokenKind::IDENTIFIER );
  delete token;

	// 1a2
  token = & lexer.getToken();
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
