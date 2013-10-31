#ifndef POS_H
#define POS_H

#include <iostream>
#include "util.h"

struct Pos
{
	explicit Pos(char const* const name) : Pos(name, 0, 0) {}

	Pos(char const* const name, unsigned const line, unsigned const column) :
		name(nonNull(name)), line(line), column(column)
	{}

  friend std::ostream & operator<<( std::ostream &out, Pos const &pos );

  void dump() const;

	char const* name;
	unsigned    line;
	unsigned    column;
};

#endif
