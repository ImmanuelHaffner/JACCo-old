#include "EntityHolderTest.h"

#include "../../src/Sema/EntityHolder.h"
#include <cstdio>

// register this test
CPPUNIT_TEST_SUITE_REGISTRATION ( EntityHolderTest );

using namespace C4;
using namespace Sema;

void EntityHolderTest::testAttach()
{
  EntityHolder h;
  Entity const * e = new Entity();
  h.attachEntity( e );
  CPPUNIT_ASSERT_EQUAL( e, h.getEntity() );
}
