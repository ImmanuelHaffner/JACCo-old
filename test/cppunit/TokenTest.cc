//===--- TokenTest.cc -----------------------------------------------------===//
//
//	~~~ The C4 Compiler TestSuite ~~~
//
//===----------------------------------------------------------------------===//

#include "TokenTest.h"

#include <cstdio>
#include <cstring>
#include "../../src/Lex/Token.h"
#include "../../src/Lex/KeywordToken.h"
#include "../../src/Lex/IdentifierToken.h"
#include "../../src/Lex/ConstantToken.h"
#include "../../src/Lex/StringLiteralToken.h"
#include "../../src/Lex/PunctuatorToken.h"
#include "../../src/Lex/EofToken.h"
#include "../../src/Lex/IllegalToken.h"


// register this test 
CPPUNIT_TEST_SUITE_REGISTRATION ( TokenTest );

using namespace C4;
using namespace Lex;


void TokenTest::setUp()
{
  this->pos = new Pos( "fileName.c" );
  text = "token text string";
}

void TokenTest::tearDown()
{
}

//
//  Tests
//

void TokenTest::testToken()
{
  Token token( *pos, TokenKind::ILLEGAL, text );

  // check pos
  CPPUNIT_ASSERT_EQUAL( pos->name, token.pos.name );
  CPPUNIT_ASSERT_EQUAL( pos->line, token.pos.line );
  CPPUNIT_ASSERT_EQUAL( pos->column, token.pos.column );

  // check token kind
  CPPUNIT_ASSERT( TokenKind::ILLEGAL == token.kind );

  // check token string
  CPPUNIT_ASSERT( strcmp( text, token.text.c_str() ) == 0 );
}

void TokenTest::testKeywordToken()
{
  KeywordToken token( *pos, KeywordKind::AUTO, text );

  // check token kind
  CPPUNIT_ASSERT( TokenKind::KEYWORD == token.kind );

  // check keyword kind
  CPPUNIT_ASSERT( KeywordKind::AUTO == token.keyword );
}

void TokenTest::testIdentifierToken()
{
  IdentifierToken token( *pos, text );

  // check token kind
  CPPUNIT_ASSERT( TokenKind::IDENTIFIER == token.kind );
}

void TokenTest::testConstantToken()
{
  ConstantToken token( *pos, text );

  // check token kind
  CPPUNIT_ASSERT( TokenKind::CONSTANT == token.kind );
}

void TokenTest::testStringLiteralToken()
{
  StringLiteralToken token( *pos, text );

  // check token kind
  CPPUNIT_ASSERT( TokenKind::STRING_LITERAL == token.kind );
}

void TokenTest::testPunctuatorToken()
{
  PunctuatorToken token( *pos, PunctuatorKind::LBRACE, text );

  // check token kind
  CPPUNIT_ASSERT( TokenKind::PUNCTUATOR == token.kind );

  // check punctuator kind
  CPPUNIT_ASSERT( PunctuatorKind::LBRACE == token.punctuator );
}

void TokenTest::testEofToken()
{
  EofToken token( *pos );

  // check token kind
  CPPUNIT_ASSERT( TokenKind::END_OF_FILE == token.kind );
}

void TokenTest::testIllegalToken()
{
  IllegalToken token( *pos, IllegalTokenKind::IDENTIFIER, "text" );

  // check token kind
  CPPUNIT_ASSERT( TokenKind::ILLEGAL == token.kind );

  // check illegal token kind
  CPPUNIT_ASSERT( IllegalTokenKind::IDENTIFIER == token.iKind );
}
