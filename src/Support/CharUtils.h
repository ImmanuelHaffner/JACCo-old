//===--- CharUtils.h-------------------------------------------------------===//
//
//  ~~~ The C4 Compiler ~~~
//
//  This file defines macros to handle chars.
//
//===----------------------------------------------------------------------===//

#ifndef CHAR_UTILS_H
#define CHAR_UTILS_H

#include <iostream>
#include <string>

inline char const * visualizeChar( char const chr )
{
  switch ( chr )
  {
    case '\?':
      return "\\?";
    case '\a':
      return "\\a";
    case '\b':
      return "\\b";
    case '\f':
      return "\\f";
    case '\n':
      return "\\n";
    case '\r':
      return "\\r";
    case '\t':
      return "\\t";
    case '\v':
      return "\\v";
    case '\0':
      return "\\0";
  }
  char * ret = new char[2];
  ret[0] = chr; ret[1] = '\0';
  return ret;
}

#endif
