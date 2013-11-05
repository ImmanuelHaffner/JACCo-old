#include "pos.h"

std::ostream & operator<<( std::ostream &out, Pos const &pos )
{
  out << pos.name << ":";

  if ( pos.line )
    out << pos.line << ":";
  if ( pos.column )
    out << pos.column << ":";

  return out;
}

void Pos::dump() const
{
  std::cout << *this;
}
