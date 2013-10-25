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

namespace C4
{
	class SourceBuffer
	{
		public:
			SourceBuffer( char const * const fileName );
			~SourceBuffer();

      /// Opens the file specified by <i>fileName<\i> and reads every single
      /// character into a buffer.
      /// Afterwards, the file is closed.
			void init();
			bool isInitialized() const;
      char const * getSourceFileName() const;
			size_t getSize() const;
			std::vector<char>::iterator getBufStart();
			std::vector<char>::iterator getBufEnd();
			std::vector<char>::const_iterator getBufStart() const;
			std::vector<char>::const_iterator getBufEnd() const;
			bool isBufEnd( std::vector<char>::iterator const &it ) const;
			bool isBufEnd( std::vector<char>::const_iterator const &it ) const;
      void dump() const;

		private:
			bool initialized;
      char const * const fileName;
			std::vector<char> *Buffer;
	};
}

#endif
