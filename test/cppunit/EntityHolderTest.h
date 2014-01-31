#ifndef ENTITY_HOLDER_TEST_H
#define ENTITY_HOLDER_TEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <cstdio>

class EntityHolderTest : public CPPUNIT_NS::TestFixture
{
  CPPUNIT_TEST_SUITE ( EntityHolderTest );
  CPPUNIT_TEST ( testAttach );
  CPPUNIT_TEST_SUITE_END ();

protected:
  void testAttach();
};

#endif
