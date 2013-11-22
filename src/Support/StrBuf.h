//===--- StrBuf.h ---------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines a string buffer for fast buffering of C-Strings.
//
//===----------------------------------------------------------------------===//

#ifndef C4_STRBUF_H
#define C4_STRBUF_H

#include <cstring>
#include <iostream>

namespace C4
{
  struct StrBuf
  {
    StrBuf();
    explicit StrBuf( size_t size );
    ~StrBuf();

    void clear();
    void append( char const * const s );
    void append( char const c );
    StrBuf& operator+=( char const * const s ) { append( s ); return *this; }
    StrBuf& operator+=( char const c ) { append( c ); return *this; }
    inline size_t getSize() { return size; }
    inline char * c_str() { return data; }
    void enlarge();

    friend std::ostream & operator<<( std::ostream &out, StrBuf const &buf );
    void dump() const { std::cout << *this; std::cout.flush(); }

    char * data;

    private:
    char * current; // points to the last element (which is '\0')
    char * end; // points to the first byte behind the buffer
    size_t size;
  }; // end struct StrBuf

  std::ostream & operator<<( std::ostream &out, StrBuf const &buf );
} // end namespace C4

#endif
