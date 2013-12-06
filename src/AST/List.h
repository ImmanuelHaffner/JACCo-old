//===--- List.h -----------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines the Abstract Syntax Tree interface.
//
//===----------------------------------------------------------------------===//

#ifndef C4_LIST_H
#define C4_LIST_H

#include <iostream>
#include <vector>
#include "../Lex/Token.h"


namespace C4
{
  namespace AST
  {
    /// List
    template< class T >
      struct List
      {
        virtual ~List() {}

        typedef typename std::vector< T const * >::iterator iterator;
        typedef typename std::vector< T const * >::const_iterator const_iterator;

        void append( T const * const t )
        {
          list.push_back( t );
        }

        List & operator+=( T const * const t )
        {
          append( t );
          return *this;
        }

        iterator begin()
        {
          return list.begin();
        }

        const_iterator begin() const
        {
          return list.begin();
        }

        iterator end()
        {
          return list.end();
        }

        const_iterator end() const
        {
          return list.end();
        }

        private:
          std::vector< T const * > list;
      }; // end struct List
  } // end namespace AST
} // end namespace C4

#endif
