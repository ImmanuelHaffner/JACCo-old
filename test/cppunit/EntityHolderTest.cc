#include "EntityHolderTest.h"

#include <cstdio>
#include "../../src/Support/Entity.h"
#include "../../src/Support/EntityHolder.h"

// register this test
CPPUNIT_TEST_SUITE_REGISTRATION ( EntityHolderTest );


using namespace C4;


void EntityHolderTest::testAttach()
{
  EntityHolder h;
  Entity *e = new Entity();
  h.attachEntity( e );
  CPPUNIT_ASSERT_EQUAL( e, h.getEntity() );
}
