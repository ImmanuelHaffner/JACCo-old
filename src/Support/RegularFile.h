//===--- RegularFile.h ----------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the tokens.
//
//===----------------------------------------------------------------------===//

#ifndef C4_REGULAR_FILE
#define C4_REGULAR_FILE

#include "File.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

namespace C4
{
  struct RegularFile : File
  {
    RegularFile() : source( std::cin )
    {}

    explicit RegularFile( std::string const &fileName )
      : RegularFile( fileName.c_str() )
    {}

    explicit RegularFile( char const * const fileName ) :
      source( *( new std::ifstream( fileName ) ) )
    {}

    ~RegularFile()
    {
      if ( source != std::cin )
        delete & source;
    }

    int get();
    int peek();
    int peek( int n );
    
    private:
    std::istream &source;
  };
} // end namespace C4

#endif
