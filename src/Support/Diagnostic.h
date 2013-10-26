//===--- Diagnostic.h -----------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines diagnostics for the C4 Compiler.
//
//===----------------------------------------------------------------------===//

#ifndef C4_DIAGNOSTIC_H
#define C4_DIAGNOSTIC_H

#include <string>
#include "../pos.h"
#include "../diagnostic.h"


namespace C4
{
  template< typename T >
  static void serialize( std::string &str, T t )
  {
    str += t;
  }

  template< typename T, typename... Args >
  static void serialize( std::string &str, T t, Args... args )
  {
    str += t;

    serialize( str, args... );
  }

  template< typename... Args >
  void ERROR( Pos const &pos, Args... args )
  {
    std::string str = "";
    serialize( str, args... );

    errorf( pos, "%s", str.c_str() );
  }
}

#endif
