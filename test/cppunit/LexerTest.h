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
  CPPUNIT_TEST ( testConstructor );
  CPPUNIT_TEST ( testEof );
  CPPUNIT_TEST ( testEolStyles );
  CPPUNIT_TEST ( testReadKeywords );
  CPPUNIT_TEST ( testReadIdentifier );
  CPPUNIT_TEST ( testReadDecimalConstant );
  CPPUNIT_TEST ( testReadNumericalAndIdentifier );
  CPPUNIT_TEST ( testReadCharacterConstant );
  CPPUNIT_TEST ( testReadStringLiteral );
  CPPUNIT_TEST ( testReadPunctuator );
  CPPUNIT_TEST ( testReadPunctuatorDigraph );
  CPPUNIT_TEST ( testReadPunctuatorDots );
  CPPUNIT_TEST ( testReadPunctuatorDigraphAmbiguity );
  CPPUNIT_TEST ( testComments );
  CPPUNIT_TEST ( testReadCommentAsWhitespace );
  CPPUNIT_TEST_SUITE_END ();

  public:
  void setUp();
  void tearDown();

  protected:
	void testConstructor();
  void testEof();
  void testEolStyles();
  void testReadKeywords();
  void testReadIdentifier();
  void testReadDecimalConstant();
  void testReadNumericalAndIdentifier();
  void testReadCharacterConstant();
  void testReadStringLiteral();
  void testReadPunctuator();
  void testReadPunctuatorDigraph();
  void testReadPunctuatorDots();
  void testReadPunctuatorDigraphAmbiguity();
  void testComments();
  void testReadCommentAsWhitespace();
};

#endif
