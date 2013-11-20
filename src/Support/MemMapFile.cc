//===--- MemMapFile.cc ----------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the tokens.
//
//===----------------------------------------------------------------------===//

#include "MemMapFile.h"

using namespace C4;

int MemMapFile::get()
{
  if ( current >= eof )
    return -1;

  int res = *current;
  ++current;

  if ( res == '\r' )
  {
    if ( *current == '\n' )
      ++current;
    return '\n';
  }

  return res;
}

int MemMapFile::peek()
{
  if ( current >= eof )
    return -1;

  if ( *current == '\r' )
    return '\n';

  return *current;
}

int MemMapFile::peek( int n )
{
  char const *p = current + n;
  if ( source.data() > p || p >= eof )
    return -1;

  if ( *p == '\r' )
    return '\n';

  return *p;
}
