//===--- ParserTest.h -----------------------------------------------------===//
//
//	~~~ The C4 Compiler TestSuite ~~~
//
//===----------------------------------------------------------------------===//

#ifndef PARSER_TEST_H
#define PARSER_TEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <cstdio>

class ParserTest : public CPPUNIT_NS::TestFixture
{
  CPPUNIT_TEST_SUITE ( ParserTest );
  CPPUNIT_TEST ( testIs );
  CPPUNIT_TEST ( testIsMulti );
  CPPUNIT_TEST_SUITE_END ();

  public:
  void setUp();
  void tearDown();

  protected:
  void testIs();
  void testIsMulti();
};

#endif
