//===--- File.h -----------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the tokens.
//
//===----------------------------------------------------------------------===//

#ifndef C4_FILE
#define C4_FILE

namespace C4
{
  struct File
  {
    virtual ~File() = 0;
    virtual int get() = 0;
    virtual int peek() = 0;
    virtual int peek( int n ) = 0;
  };
  inline File::~File() {}
} // end namespace C4

#endif
