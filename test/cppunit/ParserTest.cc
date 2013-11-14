//===--- ParserTest.cc ----------------------------------------------------===//
//
//	~~~ The C4 Compiler TestSuite ~~~
//
//===----------------------------------------------------------------------===//

#include "ParserTest.h"

#include "../../src/Lex/Lexer.h"
#include "../../src/Lex/IllegalToken.h"
#include "../../src/Parse/Parser.h"


// register this test 
CPPUNIT_TEST_SUITE_REGISTRATION ( ParserTest );

using namespace C4;
using namespace Lex;
using namespace Parse;

void ParserTest::setUp()
{
}

void ParserTest::tearDown()
{
}

void ParserTest::testIs()
{
  // redirect stdin
  std::istringstream stream( "a 0 [ ->" );
  std::streambuf * cin_bak = std::cin.rdbuf( stream.rdbuf() );
  Lexer lexer;
  Parser parser( lexer );

  CPPUNIT_ASSERT( parser.is( "a" ) );
  CPPUNIT_ASSERT( parser.is( TokenKind::IDENTIFIER ) );

  lexer.get();

  CPPUNIT_ASSERT( parser.is( "0" ) );
  CPPUNIT_ASSERT( parser.is( TokenKind::CONSTANT ) );

  lexer.get();

  CPPUNIT_ASSERT( parser.is( "[" ) );
  CPPUNIT_ASSERT( parser.is( TokenKind::PUNCTUATOR ) );

  lexer.get();

  CPPUNIT_ASSERT( parser.is( "->" ) );
  CPPUNIT_ASSERT( parser.is( TokenKind::PUNCTUATOR ) );

  lexer.get();

  CPPUNIT_ASSERT( parser.is( TokenKind::END_OF_FILE ) );


  // restode stdin
  std::cin.rdbuf( cin_bak );
}

void ParserTest::testIsMulti()
{
  // redirect stdin
  std::istringstream stream( "a ->" );
  std::streambuf * cin_bak = std::cin.rdbuf( stream.rdbuf() );
  Lexer lexer;
  Parser parser( lexer );


  CPPUNIT_ASSERT( parser.is( "a", "b", TokenKind::CONSTANT ) );
  CPPUNIT_ASSERT( parser.is( TokenKind::IDENTIFIER, "b", "" ) );

  lexer.get();

  CPPUNIT_ASSERT( parser.is( "a", "->", TokenKind::CONSTANT ) );
  CPPUNIT_ASSERT( parser.is( TokenKind::PUNCTUATOR, "b", "" ) );


  // restode stdin
  std::cin.rdbuf( cin_bak );
}
