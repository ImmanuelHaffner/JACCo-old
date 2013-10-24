//===--- SourceLocation.h -------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the SourceLocation.
//
//===----------------------------------------------------------------------===//

#ifndef SOURCE_LOCATION_H
#define SOURCE_LOCATION_H

#include <vector>
#include "../pos.h"

namespace C4
{
	struct SourceLocation
	{
		SourceLocation( Pos const &pos, std::vector<char>::iterator index ) :
			pos(pos), index(index) {}

		Pos const &pos;
		std::vector<char>::iterator const index;
	};
}

#endif
