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
#include <string>

namespace C4
{
	class SourceBuffer
	{
		public:
			SourceBuffer( char const * const fileName );
			SourceBuffer( std::string const &fileName );
			~SourceBuffer();

      /// Opens the file specified by <i>fileName<\i> and reads every single
      /// character into a buffer.
      /// Afterwards, the file is closed.
			void init();
			bool isInitialized() const;
			std::string const & getFileName() const;
			size_t size() const;
			char & operator[]( size_t n );
			char const & operator[]( size_t n ) const;
			std::vector<char>::iterator begin();
			std::vector<char>::const_iterator begin() const;
			std::vector<char>::iterator end();
			std::vector<char>::const_iterator end() const;
      void dump() const;

		private:
			bool initialized;
			std::string const fileName;
			std::vector<char> *Buffer;
	};
}

#endif
