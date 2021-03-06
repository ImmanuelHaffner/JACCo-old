//===--- Symbol.cc --------------------------------------------------------===//
//
//  ~~~ The C4 Compiler ~~~
//
//  This file implements the Symbol class for internalizing strings.
//
//===----------------------------------------------------------------------===//


#include "Symbol.h"


using namespace C4;


size_t StrHash::operator()( char const * s ) const
{
  size_t hash = 0;
  int offset = 'a' - 1;
  char const *i = s;

  while ( *i != '\0' )
  {
    hash = hash << 1 ^ ( *i - offset );
    ++i;
  }

  return hash;
}

Symbol::Table Symbol::table_( 1023 );

#ifdef _MSC_VER
static const char* duplicate(const char* s) { return _strdup(s); }
#else // _MSC_VER
static const char* duplicate(const char* s) { return strdup(s); }
#endif // _MSC_VER

void Symbol::insert( char const * s )
{
  auto it = table_.find( s );
  if ( it == table_.end() )
    it = table_.insert( duplicate(s) ).first;
  str_ = *it;
}

void Symbol::destroy()
{
  for ( auto s : table_ )
    free( (void*) const_cast< char * >( s ) );
  table_.clear();
}
