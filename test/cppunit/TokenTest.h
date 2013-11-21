//===--- TokenTest.h ------------------------------------------------------===//
//
//	~~~ The C4 Compiler TestSuite ~~~
//
//===----------------------------------------------------------------------===//

#ifndef TOKEN_TEST_H
#define TOKEN_TEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "../../src/pos.h"

class TokenTest : public CPPUNIT_NS::TestFixture
{
  CPPUNIT_TEST_SUITE ( TokenTest );
  CPPUNIT_TEST ( testToken );
  CPPUNIT_TEST_SUITE_END ();

  public:
  void setUp();
  void tearDown();

  protected:
  void testToken();

  private:
  Pos * pos;
  char const * text;
};

#endif
