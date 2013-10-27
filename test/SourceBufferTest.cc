//===--- SourceBufferTest.cc ----------------------------------------------===//
//
//	~~~ The C4 Compiler TestSuite ~~~
//
//===----------------------------------------------------------------------===//

#include "SourceBufferTest.h"

#include <cstdio>
#include <cstring>
#include "../src/Support/SourceBuffer.h"


// register this test 
CPPUNIT_TEST_SUITE_REGISTRATION ( SourceBufferTest );

using namespace C4;


void SourceBufferTest::setUp()
{
}

void SourceBufferTest::tearDown()
{
}

void SourceBufferTest::testConstructor()
{
	SourceBuffer buf( "resource/testSourceBufferInit01.c" );

	CPPUNIT_ASSERT_EQUAL( false, buf.isInitialized() );
}

void SourceBufferTest::testInit()
{
	SourceBuffer buf( "resource/testSourceBufferInit01.c" );
	buf.init();

	// test isInitialized
	CPPUNIT_ASSERT( buf.isInitialized() );

	// test file name
	CPPUNIT_ASSERT( buf.getSourceFileName() == "resource/testSourceBufferInit01.c" );

	// test buffer values
	CPPUNIT_ASSERT_EQUAL( 'a', buf[0] );
	CPPUNIT_ASSERT_EQUAL( 'z', buf[25] );
	CPPUNIT_ASSERT_EQUAL( '\n', buf[26] );

	CPPUNIT_ASSERT_EQUAL( 'A', buf[27] );
	CPPUNIT_ASSERT_EQUAL( 'Z', buf[52] );
	CPPUNIT_ASSERT_EQUAL( '\n', buf[53] );

	CPPUNIT_ASSERT_EQUAL( '1', buf[54] );
	CPPUNIT_ASSERT_EQUAL( '0', buf[63] );
	CPPUNIT_ASSERT_EQUAL( '\n', buf[64] );
	
	CPPUNIT_ASSERT_EQUAL( '[', buf[65] );
	CPPUNIT_ASSERT_EQUAL( ';', buf[89] );

	CPPUNIT_ASSERT_EQUAL( 90uL, buf.size() );
}

void SourceBufferTest::testIterator()
{
	SourceBuffer buf( "resource/testSourceBufferInit01.c" );
	buf.init();

	auto it = buf.begin();

	CPPUNIT_ASSERT( it != buf.end() );

	CPPUNIT_ASSERT_EQUAL( 'a', *it );
	++it;
	CPPUNIT_ASSERT_EQUAL( 'b', *it );

	while ( it != buf.end() )
		++it;

	--it;
	CPPUNIT_ASSERT_EQUAL( ';', *it );
}
