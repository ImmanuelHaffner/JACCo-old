//===--- SourceBufferTest.h -----------------------------------------------===//
//
//	~~~ The C4 Compiler TestSuite ~~~
//
//===----------------------------------------------------------------------===//

#ifndef SOURCE_BUFFER_TEST_H
#define SOURCE_BUFFER_TEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class SourceBufferTest : public CPPUNIT_NS::TestFixture
{
  CPPUNIT_TEST_SUITE ( SourceBufferTest );
	CPPUNIT_TEST ( testConstructor );
	CPPUNIT_TEST ( testInit );
	CPPUNIT_TEST ( testIterator );
  CPPUNIT_TEST_SUITE_END ();

  public:
  void setUp();
  void tearDown();

  protected:
  void testConstructor();
  void testInit();
	void testIterator();

};

#endif
