#include "EntityHolderTest.h"

#include "../../src/Sema/EntityHolder.h"
#include <cstdio>

// register this test
CPPUNIT_TEST_SUITE_REGISTRATION ( EntityHolderTest );

using namespace C4;
using namespace Sema;

void EntityHolderTest::testExceptionCallAgain()
{
  EntityHolder h;
  h.attachEntity(NULL);
  std::string message;
  try
  {
    h.attachEntity(NULL);
  }
  catch(EntityHolderException const& e)
  {
    message = e.what();
  }
  CPPUNIT_ASSERT_EQUAL_MESSAGE(message, true, !message.empty());
}
