#include "pos.h"

std::ostream & operator<<( std::ostream &out, Pos const &pos )
{
  out << pos.name;

  if ( pos.line && pos.column )
    out << pos.line << ":" << pos.column;
  else if ( pos.line )
    out << pos.line;
  else if ( pos.column )
    out << pos.column;

  return out;
}

void Pos::dump() const
{
  std::cout << *this;
}
