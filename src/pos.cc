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

bool operator==( Pos const &p0, Pos const &p1 )
{
  return strEq( p0.name, p1.name ) &&
    p0.line == p1.line &&
    p0.column == p1.column;
}

void Pos::dump() const
{
  std::cout << this << std::endl;
}
