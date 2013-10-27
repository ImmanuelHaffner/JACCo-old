//===--- SourceBuffer.cc --------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file implements the SourceBuffer.
//
//===----------------------------------------------------------------------===//

#include "SourceBuffer.h"

#include <cassert>
#include <iostream>
#include <cstdio>
#include "Diagnostic.h"
#include "../pos.h"

using namespace C4;

SourceBuffer::SourceBuffer( char const * const fileName ) :
  initialized(false), fileName(fileName), Buffer(NULL)
{
	assert( fileName != NULL && "fileName must not be NULL" );
}

SourceBuffer::SourceBuffer( std::string const &fileName ) :
  initialized(false), fileName(fileName), Buffer(NULL)
{}

SourceBuffer::~SourceBuffer()
{
	if ( initialized )
		delete Buffer;
}

void SourceBuffer::init()
{
  FILE * file = NULL;
  if ( fileName == "<stdin>" )
  {
    file = stdin;
  }
  else
    file = fopen( fileName.c_str(), "rb" );

  if ( ! file )
		ERROR( Pos( fileName.c_str() ), "file does not exist" );

	Buffer = new std::vector<char>();

	int c;
	while ( (c = getc( file )) != EOF )
		Buffer->push_back( c );

	// EOF hack
	Buffer->pop_back();

  fclose ( file );
	initialized = true;
}

bool SourceBuffer::isInitialized() const
{
	return initialized;
}

std::string const & SourceBuffer::getFileName() const
{
  return fileName;
}

size_t SourceBuffer::size() const
{
	return Buffer->size();
}

char & SourceBuffer::operator[]( size_t n )
{
	return (*Buffer)[n];
}

char const & SourceBuffer::operator[]( size_t n ) const
{
	return (*Buffer)[n];
}

std::vector<char>::iterator SourceBuffer::begin()
{
	return Buffer->begin();
}

std::vector<char>::iterator SourceBuffer::end()
{
	return Buffer->end();
}

std::vector<char>::const_iterator SourceBuffer::begin() const
{
	return Buffer->begin();
}

std::vector<char>::const_iterator SourceBuffer::end() const
{
	return Buffer->end();
}

void SourceBuffer::dump() const
{
  std::cout << fileName << ":" << std::endl;

  if ( ! initialized )
  {
    std::cout << "\tnot initialized";
  }

  for ( auto it = begin(); it != end(); ++it )
  {
    std::cout << *it;
  }
  std::cout << std::endl;
}
