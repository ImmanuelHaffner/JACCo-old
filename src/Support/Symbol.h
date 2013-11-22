//===--- Symbol.h ---------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the tokens.
//
//===----------------------------------------------------------------------===//

#ifndef C4_SYMBOL
#define C4_SYMBOL

#include <functional>
#include <cstring>
#include <string>
#include <unordered_set>

namespace C4
{
  struct StrHash
  {
    size_t operator()( char const * s ) const;
  };

  struct StrEqual
  {
    bool operator()( char const * s1, char const * s2 ) const
    {
      return std::strcmp( s1, s2 ) == 0;
    }
  };

  class Symbol
  {
    public:
      Symbol() { insert( "" ); }
      Symbol( char const * const s ) { insert( s ); }
      Symbol( std::string const &s ) { insert( s.c_str() ); }

      char const * str() const { return str_; }
      bool operator==( Symbol symbol ) const { return str() == symbol.str(); }
      bool operator!=( Symbol symbol ) const { return str() != symbol.str(); }

      static void destroy();
      static inline size_t size()
      {
        return table_.size();
      }

    private:
      void insert(const char* str);

      const char * str_;
      typedef std::unordered_set< char const *, StrHash, StrEqual > Table;
      static Table table_;
  };

  inline std::ostream & operator<<( std::ostream &out, Symbol s )
  {
    return out << s.str();
  }
} // end namespace C4

namespace std {

  template<>
    struct hash< C4::Symbol >
    {
      size_t operator()( C4::Symbol symbol ) const
      {
        return std::hash< char const * >()( symbol.str() );
      }
    };
} // end namespace std

#endif
