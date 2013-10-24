//===--- SourceBuffer.h ---------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the SourceBuffer.
//
//===----------------------------------------------------------------------===//

#ifndef SOURCE_BUFFER_H
#define SOURCE_BUFFER_H

#include <cstdio>
#include <vector>

namespace C4{
	class SourceBuffer
	{
		public:
			SourceBuffer( FILE * file );
			~SourceBuffer();

			void init();
			bool isInitialized() const;
			size_t getSize() const;
			std::vector<char>::iterator getBufStart();
			std::vector<char>::iterator getBufEnd();
			std::vector<char>::const_iterator getBufStart() const;
			std::vector<char>::const_iterator getBufEnd() const;
			bool isBufEnd( std::vector<char>::iterator &it ) const;

		private:
			bool initialized;
			FILE *file;
			std::vector<char> *Buffer;
	};
}

#endif
