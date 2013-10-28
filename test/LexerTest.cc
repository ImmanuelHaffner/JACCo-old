//===--- LexerTest.cc -----------------------------------------------------===//
//
//	~~~ The C4 Compiler TestSuite ~~~
//
//===----------------------------------------------------------------------===//

#include "LexerTest.h"

#include "../src/Lex/Lexer.h"


// register this test 
CPPUNIT_TEST_SUITE_REGISTRATION ( LexerTest );

using namespace C4;
using namespace Lex;

void LexerTest::setUp()
{
}

void LexerTest::tearDown()
{
	if ( file )
		fclose( file );
}


void LexerTest::testLexerConstructor()
{
	char const * const fileName = "resource/allowedCharacters.c";
	file = fopen( fileName, "rb" );

	Lexer lexer( fileName, file );

	// check file name
	CPPUNIT_ASSERT( strcmp( fileName, lexer.fileName.c_str() ) == 0 );

	// check pos
	CPPUNIT_ASSERT( strcmp( fileName, lexer.getPos().name ) == 0 );
	CPPUNIT_ASSERT_EQUAL( 1u, lexer.getPos().line );
	CPPUNIT_ASSERT_EQUAL( 0u, lexer.getPos().column );
}

void LexerTest::testStep()
{
	file = fopen( "resource/allowedCharacters.c", "rb" );
}
