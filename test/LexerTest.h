//===--- LexerTest.h ------------------------------------------------------===//
//
//	~~~ The C4 Compiler TestSuite ~~~
//
//===----------------------------------------------------------------------===//

#ifndef LEXER_TEST_H
#define LEXER_TEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <cstdio>

class LexerTest : public CPPUNIT_NS::TestFixture
{
  CPPUNIT_TEST_SUITE ( LexerTest );
  CPPUNIT_TEST ( testLexerConstructor );
  CPPUNIT_TEST ( testStep );
  CPPUNIT_TEST_SUITE_END ();

  public:
  void setUp();
  void tearDown();

  protected:
	void testLexerConstructor();
  void testStep();

	private:
	FILE * file;
};

#endif
