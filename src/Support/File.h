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
    virtual ~File() {}
    virtual int get() = 0;
    virtual int peek() = 0;
    virtual int peek( int c ) = 0;
  };
} // end namespace C4

#endif
