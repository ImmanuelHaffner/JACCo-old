//===--- MemMapFile.cc ----------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the tokens.
//
//===----------------------------------------------------------------------===//

#include "MemMapFile.h"

#include <cstdio>


using namespace C4;


int MemMapFile::get()
{
  if ( current >= eof )
    return EOF;

  int res = (unsigned char) *current;
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
    return EOF;

  if ( *current == '\r' )
    return '\n';

  return (unsigned char) *current;
}

int MemMapFile::peek( int n )
{
  char const *p = current + n;
  if ( source.data() > p || p >= eof )
    return EOF;

  if ( *p == '\r' )
    return '\n';

  return (unsigned char) *p;
}
