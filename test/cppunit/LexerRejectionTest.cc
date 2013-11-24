//===--- LexerRejectionTest.cc --------------------------------------------===//
//
//	~~~ The C4 Compiler TestSuite ~~~
//
//===----------------------------------------------------------------------===//

#include "LexerRejectionTest.h"

#include <cstring>
#include "../../src/diagnostic.h"
#include "../../src/Lex/Lexer.h"


// register this test 
CPPUNIT_TEST_SUITE_REGISTRATION ( LexerRejectionTest );

using namespace C4;
using namespace Lex;

void LexerRejectionTest::setUp()
{
  hasNewErrors();
  out_bak = std::cout.rdbuf( out_buf.rdbuf() );
  err_bak = std::cerr.rdbuf( err_buf.rdbuf() );
}

void LexerRejectionTest::tearDown()
{
  //assert( ! hasNewErrors() && "unhandled error message" );
  std::cout.rdbuf( out_bak );
  std::cerr.rdbuf( err_bak );
}


void LexerRejectionTest::testEmptyCharConst()
{
  Lexer lexer;

  // redirect stdin
  std::istringstream stream( "''''" );
  std::streambuf * cin_bak = std::cin.rdbuf( stream.rdbuf() );

	// ''
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::CONSTANT );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.column );
    CPPUNIT_ASSERT( strEq( token.sym.str(), "''" ) );
    CPPUNIT_ASSERT( hasNewErrors() );
  }

	// ''
  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind  == TK::CONSTANT );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 3u, token.pos.column );
    CPPUNIT_ASSERT( strEq( token.sym.str(), "''" ) );
    CPPUNIT_ASSERT( hasNewErrors() );
  }


  // restode stdin
  std::cin.rdbuf( cin_bak );
}

void LexerRejectionTest::testIllegalComments()
{
  Lexer lexer;

  // redirect stdin
  std::istringstream stream( "/*" );
  std::streambuf * cin_bak = std::cin.rdbuf( stream.rdbuf() );


  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind == TK::END_OF_FILE );
    CPPUNIT_ASSERT_EQUAL( 1u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 2u, token.pos.column );
    CPPUNIT_ASSERT( hasNewErrors() );
  }


  // redirect stdin
  stream.str( "\n/*/" );
  std::cin.rdbuf( stream.rdbuf() );

  {
    Token token = lexer.getToken();
    CPPUNIT_ASSERT( token.kind == TK::END_OF_FILE );
    CPPUNIT_ASSERT_EQUAL( 2u, token.pos.line );
    CPPUNIT_ASSERT_EQUAL( 3u, token.pos.column );
    CPPUNIT_ASSERT( hasNewErrors() );
  }


  // restode stdin
  std::cin.rdbuf( cin_bak );
}
