//===--- MemMapFile.h -----------------------------------------------------===//
//
//  ~~~ The C4 Compiler ~~~
//
//  This file defines the tokens.
//
//===----------------------------------------------------------------------===//

#ifndef C4_MEM_MAP_FILE
#define C4_MEM_MAP_FILE

#include "File.h"

#include <string>
#include "memory_file.h"

namespace C4
{
  struct MemMapFile : File
  {
    explicit MemMapFile( std::string const &fileName )
      : MemMapFile( fileName.c_str() )
    {}

    explicit MemMapFile( char const * const fileName ) :
      source( fileName ), current( source.data() ),
      eof( source.data() + source.size() )
    {}

    ~MemMapFile() {}

    int get();
    int peek();
    int peek( int n );
    
    private:
    InputMemoryFile source;
    char const * current;
    char const * const eof; // points to the first byte BEHIND the buffer
  };
} // end namespace C4

#endif
