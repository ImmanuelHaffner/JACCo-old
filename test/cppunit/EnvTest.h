//===--- EnvTest.h --------------------------------------------------------===//
//
//	~~~ The C4 Compiler TestSuite ~~~
//
//===----------------------------------------------------------------------===//


#ifndef ENV_TEST_H
#define ENV_TEST_H


#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <cstdio>

class EnvTest : public CPPUNIT_NS::TestFixture
{
  CPPUNIT_TEST_SUITE ( EnvTest );
  CPPUNIT_TEST ( testScopeInsert );
  CPPUNIT_TEST ( testScopeInsertType );
  CPPUNIT_TEST ( testEnvPushScope );
  CPPUNIT_TEST_SUITE_END ();

  public:
  void setUp();
  void tearDown();

  protected:
	void testScopeInsert();
	void testScopeInsertType();

  void testEnvPushScope();
};


#endif
