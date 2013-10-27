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
#include "../pos.h"
#include "../diagnostic.h"

using namespace C4;

SourceBuffer::SourceBuffer( char const * const fileName ) :
  initialized(false), fileName(fileName)
{
	assert( fileName != NULL && "fileName must not be NULL" );
}

SourceBuffer::~SourceBuffer()
{
	delete Buffer;
}

void SourceBuffer::init()
{
  FILE * file = NULL;
  if ( strEq( "<stdin>", fileName ) )
  {
    file = stdin;
  }
  else
    file = fopen( fileName, "rb" );

  if ( ! file )
    errorErrno( Pos( fileName ) );

	Buffer = new std::vector<char>();

	int c;
	while ( (c = getc( file )) != EOF )
		Buffer->push_back( c );

  fclose ( file );
	initialized = true;
}

bool SourceBuffer::isInitialized() const
{
	return initialized;
}

char const * SourceBuffer::getSourceFileName() const
{
  return fileName;
}

size_t SourceBuffer::getSize() const
{
	return Buffer->size();
}

std::vector<char>::iterator SourceBuffer::getBufStart()
{
	return Buffer->begin();
}

std::vector<char>::iterator SourceBuffer::getBufEnd()
{
	return Buffer->end();
}

std::vector<char>::const_iterator SourceBuffer::getBufStart() const
{
	return Buffer->begin();
}

std::vector<char>::const_iterator SourceBuffer::getBufEnd() const
{
	return Buffer->end();
}

bool SourceBuffer::isBufEnd( std::vector<char>::iterator const &it ) const
{
	return it == Buffer->end();
}

bool SourceBuffer::isBufEnd( std::vector<char>::const_iterator const &it ) const
{
	return it == Buffer->end();
}

void SourceBuffer::dump() const
{
  std::cout << fileName << ":" << std::endl;

  if ( ! initialized )
  {
    std::cout << "\tnot initialized";
  }

  for ( auto it = getBufStart(); ! isBufEnd( it ); ++it )
  {
    std::cout << *it;
  }
  std::cout << std::endl;
}
