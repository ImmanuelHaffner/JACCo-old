//===--- TypeFactoryTest.cc -----------------------------------------------===//
//
//	~~~ The C4 Compiler TestSuite ~~~
//
//===----------------------------------------------------------------------===//

#include "TypeFactoryTest.h"

#include "../../src/Sema/SemaTypeFactory.h"


using namespace C4;
using namespace Sema;


// register this test 
CPPUNIT_TEST_SUITE_REGISTRATION ( TypeFactoryTest );

static TypeFactory * tf;


void TypeFactoryTest::setUp()
{
  tf = new TypeFactory();
}

void TypeFactoryTest::tearDown()
{
  tf->destroy();
  delete tf;
}


void TypeFactoryTest::testDestroy()
{
  TypeFactory tf;

  CPPUNIT_ASSERT_EQUAL( 0u, (unsigned) tf.sizeP() );
  CPPUNIT_ASSERT_EQUAL( 0u, (unsigned) tf.sizeF() );

  tf.getPtr( tf.getVoid() );
  tf.getPtr( tf.getInt() );
  // TODO insert function types

  CPPUNIT_ASSERT( 0u != (unsigned) tf.sizeP() );
  // TODO CPPUNIT_ASSERT( 0u != (unsigned) tf.sizeF() );

  tf.destroy();
  CPPUNIT_ASSERT_EQUAL( 0u, (unsigned) tf.sizeP() );
  CPPUNIT_ASSERT_EQUAL( 0u, (unsigned) tf.sizeF() );
}

void TypeFactoryTest::testSimpleTypes()
{
  Type const * const v0 = tf->getVoid();
  Type const * const c0 = tf->getChar();
  Type const * const i0 = tf->getInt();
  Type const * const v1 = tf->getVoid();
  Type const * const c1 = tf->getChar();
  Type const * const i1 = tf->getInt();

  CPPUNIT_ASSERT_EQUAL( v0, v1 );
  CPPUNIT_ASSERT_EQUAL( c0, c1 );
  CPPUNIT_ASSERT_EQUAL( i0, i1 );

  CPPUNIT_ASSERT_EQUAL( 0u, (unsigned) tf->sizeP() );
  CPPUNIT_ASSERT_EQUAL( 0u, (unsigned) tf->sizeF() );
}

void TypeFactoryTest::testPtrTypes()
{
  // Create simple types
  Type const * const v = tf->getVoid();
  Type const * const i = tf->getInt();
  
  // Create 5 pointer types
  Type const * const vp0 = tf->getPtr( v );
  Type const * const ip0 = tf->getPtr( i );
  Type const * const vp1 = tf->getPtr( v );
  Type const * const ip1 = tf->getPtr( i );
  tf->getPtr( tf->getChar() );

  CPPUNIT_ASSERT_EQUAL( vp0, vp1 );
  CPPUNIT_ASSERT_EQUAL( ip0, ip1 );

  CPPUNIT_ASSERT_EQUAL( 3u, (unsigned) tf->sizeP() );
  CPPUNIT_ASSERT_EQUAL( 0u, (unsigned) tf->sizeF() );
}
