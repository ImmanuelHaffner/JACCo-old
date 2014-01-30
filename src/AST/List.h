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
#include "Printable.h"
#include "../Lex/Token.h"


namespace C4
{
  namespace AST
  {
    /// List
    template< class T >
      struct List : Printable
      {
				List() {}
				List( std::vector< T const * > &list ) : list(list) {}
        virtual ~List() {}

        typedef typename std::vector< T const * >::iterator iterator;
        typedef typename std::vector< T const * >::const_iterator const_iterator;

        inline size_t size() const { return list.size(); }
        void append( T const * const t );
        List & operator+=( T const * const t );
        iterator begin();
        const_iterator begin() const;
        iterator end();
        const_iterator end() const;

        private:
				std::vector< T const * > list;
      }; // end struct List

    template< class T >
      void List<T>::append( T const * const t )
      {
        assert( t && "must not append NULL" );
        list.push_back( t );
      }

    template< class T >
      List<T> & List<T>::operator+=( T const * const t )
      {
        append( t );
        return *this;
      }

    template< class T >
      typename List<T>::iterator List<T>::begin()
      {
        return list.begin();
      }

    template< class T >
      typename List<T>::const_iterator List<T>::begin() const
      {
        return list.begin();
      }

    template< class T >
      typename List<T>::iterator List<T>::end()
      {
        return list.end();
      }

    template< class T >
      typename List<T>::const_iterator List<T>::end() const
      {
        return list.end();
      }

  } // end namespace AST
} // end namespace C4

#endif
