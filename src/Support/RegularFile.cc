//===--- RegularFile.cc ---------------------------------------------------===//
//
//  ~~~ The C4 Compiler ~~~
//
//  This file defines the tokens.
//
//===----------------------------------------------------------------------===//

#include "RegularFile.h"


using namespace C4;


int RegularFile::get()
{
  int res = source.get();

  if ( res == '\r' )
  {
    if ( source.peek() == '\n' )
      source.get();
    return '\n';
  }
  return res;
}

int RegularFile::peek()
{
  return source.peek();
}

int RegularFile::peek( int n )
{
  // XXX Ungetting multiple chars from cin should NOT work, however, it does o.O
  for ( int i = 0; i < n; ++i )
    source.get();
  int c = source.peek();
  for ( int i = 0; i < n; ++i )
    source.unget();

  return c;
}
