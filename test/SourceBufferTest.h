//===--- SourceBufferTest.h -----------------------------------------------===//
//
//	~~~ The C4 Compiler TestSuite ~~~
//
//===----------------------------------------------------------------------===//

#ifndef SOURCE_BUFFER_TEST_H
#define SOURCE_BUFFER_TEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "../src/Support/SourceBuffer.h"

class SourceBufferTest : public CPPUNIT_NS::TestFixture
{
  CPPUNIT_TEST_SUITE ( SourceBufferTest );
	CPPUNIT_TEST ( test );
  CPPUNIT_TEST_SUITE_END ();

  public:
  void setUp();
  void tearDown();

  protected:
  void test();

};

#endif
