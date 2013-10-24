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

using namespace C4;

SourceBuffer::SourceBuffer( FILE *file ) : initialized(false), file(file)
{
	assert( file != NULL && "file must not be NULL" );
}

SourceBuffer::~SourceBuffer()
{
	delete Buffer;
}

void SourceBuffer::init()
{
	Buffer = new std::vector<char>();

	int c;
	while ( (c = getc( file )) != EOF )
		Buffer->push_back( c );

	initialized = true;
}

bool SourceBuffer::isInitialized() const
{
	return initialized;
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

bool SourceBuffer::isBufEnd( std::vector<char>::iterator &it ) const
{
	return it == Buffer->end();
}
