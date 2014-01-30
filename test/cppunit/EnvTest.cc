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

void EnvTest::testInit()
{
  Env env;

  CPPUNIT_ASSERT_EQUAL( (size_t) 1, env.depth() );
}

void EnvTest::testPushPop()
{
  Env env;

  env.pushScope();
  CPPUNIT_ASSERT_EQUAL( (size_t) 2, env.depth() );

  env.pushScope();
  env.pushScope();
  env.pushScope();
  CPPUNIT_ASSERT_EQUAL( (size_t) 5, env.depth() );

  env.popScope();
  CPPUNIT_ASSERT_EQUAL( (size_t) 4, env.depth() );

  env.popScope();
  env.popScope();
  env.popScope();
  CPPUNIT_ASSERT_EQUAL( (size_t) 1, env.depth() );
}

void EnvTest::testInsert()
{
  Env env;
  Type const * const t_a0 = TypeFactory::getInt();
  Type const * const t_b0 = TypeFactory::getChar();

  // Check insert id.
  Entity const * const e_a0 = env.insert( "id_a" );
  CPPUNIT_ASSERT( e_a0 != NULL );
  Entity const * const e_b0 = env.insert( "id_b" );
  CPPUNIT_ASSERT( e_b0 != NULL );

  // Check insert type.
  CPPUNIT_ASSERT( env.insert( "t_a", t_a0 ) );
  CPPUNIT_ASSERT( env.insert( "t_b", t_b0 ) );

  // Check double insert.
  CPPUNIT_ASSERT( env.insert( "id_a" ) == NULL );
  CPPUNIT_ASSERT( ! env.insert( "t_a", t_a0 ) );

  // Check lookup.
  CPPUNIT_ASSERT_EQUAL( e_a0, env.lookup( "id_a" ) );
  CPPUNIT_ASSERT_EQUAL( e_b0, env.lookup( "id_b" ) );
  CPPUNIT_ASSERT_EQUAL( t_a0, env.lookupType( "t_a" ) );
  CPPUNIT_ASSERT_EQUAL( t_b0, env.lookupType( "t_b" ) );


  // Push a new scope.
  env.pushScope();

  Type const * const t_a1 = TypeFactory::getVoid();

  // Check insert id.
  Entity const * const e_a1 = env.insert( "id_a" );
  CPPUNIT_ASSERT( e_a1 != NULL );

  // Check that a new entity has been created.
  CPPUNIT_ASSERT( e_a0 != e_a1 );

  // Check insert type.
  CPPUNIT_ASSERT( env.insert( "t_a", t_a1 ) );

  // Check lookup (including elements from previous scope).
  CPPUNIT_ASSERT_EQUAL( e_a1, env.lookup( "id_a" ) );
  CPPUNIT_ASSERT_EQUAL( e_b0, env.lookup( "id_b" ) );
  CPPUNIT_ASSERT_EQUAL( t_a1, env.lookupType( "t_a" ) );
  CPPUNIT_ASSERT_EQUAL( t_b0, env.lookupType( "t_b" ) );
}
