//===--- StrBuf.cc --------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements a string buffer for fast buffering of C-Strings.
//
//===----------------------------------------------------------------------===//

#include "StrBuf.h"

#include <cassert>
#include <cstdlib>

using namespace C4;

StrBuf::StrBuf() : StrBuf( 256 )
{}

StrBuf::StrBuf( size_t size ) : data( (char*) calloc( size, 1 )  ),
  current( data ), end( data + size ), size( size )
{}

StrBuf::~StrBuf()
{
  free( data );
}

void StrBuf::clear()
{
  if ( current > data )
  {
    memset( data, '\0', current - data );
    current = data;
  }
}

void StrBuf::append( char const * const s )
{
  size_t len = strlen( s );
  while ( current + len >= end )
    enlarge();

  strcpy( current, s );
  current += len;
}

void StrBuf::append( char const c )
{
  if ( current + 1 >= end )
    enlarge();

  *current = c;
  ++current;
}

void StrBuf::enlarge()
{
  size_t NEW_size = size * 2;
  char * NEW_data = (char*) calloc( NEW_size, 1 );
  char * NEW_end = NEW_data + NEW_size;
  char * NEW_current = NEW_data + ( current - data );

  memcpy( NEW_data, data, size );
  delete data;

  data = NEW_data;
  size = NEW_size;
  end = NEW_end;
  current = NEW_current;

  assert( (size_t) ( end - data) == size && "wrong size or borders" );
}
