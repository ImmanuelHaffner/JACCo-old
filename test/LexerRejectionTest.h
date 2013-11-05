//===--- LexerRejectionTest.h ---------------------------------------------===//
//
//	~~~ The C4 Compiler TestSuite ~~~
//
//===----------------------------------------------------------------------===//

#ifndef LEXER_REJECTION_TEST_H
#define LEXER_REJECTION_TEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <cstdio>

class LexerRejectionTest : public CPPUNIT_NS::TestFixture
{
  CPPUNIT_TEST_SUITE ( LexerRejectionTest );
  CPPUNIT_TEST ( testEmptyCharConst );
  CPPUNIT_TEST ( testIllegalIdentifiers );
  CPPUNIT_TEST ( testIllegalComments );
  CPPUNIT_TEST_SUITE_END ();

  public:
  void setUp();
  void tearDown();

  protected:
	void testEmptyCharConst();
	void testIllegalIdentifiers();
	void testIllegalComments();
};

#endif
