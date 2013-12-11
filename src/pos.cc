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

std::ostream & operator<<( std::ostream &out, Pos const * const pos )
{
  return out << *pos;
}

void Pos::dump() const
{
  std::cout << this << std::endl;
}
