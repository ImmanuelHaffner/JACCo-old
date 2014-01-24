//===--- TypeFactoryTest.h ------------------------------------------------===//
//
//	~~~ The C4 Compiler TestSuite ~~~
//
//===----------------------------------------------------------------------===//

#ifndef TYPE_FACTORY_TEST
#define TYPE_FACTORY_TEST

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <cstdio>

class TypeFactoryTest : public CPPUNIT_NS::TestFixture
{
  CPPUNIT_TEST_SUITE ( TypeFactoryTest );
  CPPUNIT_TEST ( testDestroy );
  CPPUNIT_TEST ( testSimpleTypes );
  CPPUNIT_TEST ( testPtrTypes );
  CPPUNIT_TEST_SUITE_END ();

  public:
  void setUp();
  void tearDown();

  protected:
  void testDestroy();
  void testSimpleTypes();
  void testPtrTypes();
};

#endif
