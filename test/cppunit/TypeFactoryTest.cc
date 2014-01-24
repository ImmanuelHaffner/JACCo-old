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


void TypeFactoryTest::setUp()
{
}

void TypeFactoryTest::tearDown()
{
  TypeFactory::destroy();
}


void TypeFactoryTest::testDestroy()
{
  CPPUNIT_ASSERT_EQUAL( 0u, (unsigned) TypeFactory::sizeP() );
  CPPUNIT_ASSERT_EQUAL( 0u, (unsigned) TypeFactory::sizeF() );

  TypeFactory::getPtr( TypeFactory::getVoid() );
  TypeFactory::getPtr( TypeFactory::getInt() );
  // TODO insert function types

  CPPUNIT_ASSERT( 0u != (unsigned) TypeFactory::sizeP() );
  // TODO CPPUNIT_ASSERT( 0u != (unsigned) TypeFactory::sizeF() );

  TypeFactory::destroy();
  CPPUNIT_ASSERT_EQUAL( 0u, (unsigned) TypeFactory::sizeP() );
  CPPUNIT_ASSERT_EQUAL( 0u, (unsigned) TypeFactory::sizeF() );
}

void TypeFactoryTest::testSimpleTypes()
{
  Type const * const v0 = TypeFactory::getVoid();
  Type const * const c0 = TypeFactory::getChar();
  Type const * const i0 = TypeFactory::getInt();
  Type const * const v1 = TypeFactory::getVoid();
  Type const * const c1 = TypeFactory::getChar();
  Type const * const i1 = TypeFactory::getInt();

  CPPUNIT_ASSERT_EQUAL( v0, v1 );
  CPPUNIT_ASSERT_EQUAL( c0, c1 );
  CPPUNIT_ASSERT_EQUAL( i0, i1 );

  CPPUNIT_ASSERT_EQUAL( 0u, (unsigned) TypeFactory::sizeP() );
  CPPUNIT_ASSERT_EQUAL( 0u, (unsigned) TypeFactory::sizeF() );
}

void TypeFactoryTest::testPtrTypes()
{
  // Create simple types
  Type const * const v = TypeFactory::getVoid();
  Type const * const i = TypeFactory::getInt();
  
  // Create 5 pointer types
  Type const * const vp0 = TypeFactory::getPtr( v );
  Type const * const ip0 = TypeFactory::getPtr( i );
  Type const * const vp1 = TypeFactory::getPtr( v );
  Type const * const ip1 = TypeFactory::getPtr( i );
  TypeFactory::getPtr( TypeFactory::getChar() );

  CPPUNIT_ASSERT_EQUAL( vp0, vp1 );
  CPPUNIT_ASSERT_EQUAL( ip0, ip1 );

  CPPUNIT_ASSERT_EQUAL( 3u, (unsigned) TypeFactory::sizeP() );
  CPPUNIT_ASSERT_EQUAL( 0u, (unsigned) TypeFactory::sizeF() );
}
