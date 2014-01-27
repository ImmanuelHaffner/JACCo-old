//===--- EnvTest.cc -------------------------------------------------------===//
//
//	~~~ The C4 Compiler TestSuite ~~~
//
//===----------------------------------------------------------------------===//


#include "EnvTest.h"

#include "../../src/Sema/Env.h"
#include "../../src/Sema/SemaTypeFactory.h"
#include "../../src/util.h"


// register this test 
CPPUNIT_TEST_SUITE_REGISTRATION ( EnvTest );


using namespace C4;
using namespace Sema;


void EnvTest::setUp()
{
}

void EnvTest::tearDown()
{
}


void EnvTest::testScopeInsert()
{
  Scope scope;

  // Check empty scope lookup.
  CPPUNIT_ASSERT( scope.lookup( "a" ) == NULL );

  // Check first insert.
  Entity const * const ea = scope.insert( "a" );
  CPPUNIT_ASSERT( ea != NULL );

  // Check lookup.
  CPPUNIT_ASSERT_EQUAL( ea, scope.lookup( "a" ) );

  // Check double insert.
  CPPUNIT_ASSERT( scope.insert( "a" ) == NULL );
}

void EnvTest::testScopeInsertType()
{
  Scope scope;
  Type const * const t = TypeFactory::getInt();

  // Check empty scope lookup.
  CPPUNIT_ASSERT( scope.lookupType( "a" ) == NULL );

  // Check first insert.
  CPPUNIT_ASSERT( scope.insert( "a", t ) );

  // Check lookup.
  CPPUNIT_ASSERT_EQUAL( t, scope.lookupType( "a" ) );

  // Check double insert.
  CPPUNIT_ASSERT( scope.insert( "a", t ) == false );
}

void EnvTest::testEnvPushScope()
{
  // TODO
  CPPUNIT_ASSERT( false /* implement further tests */ );
}
