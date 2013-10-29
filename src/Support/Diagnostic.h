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
#include <cstring>
#include <cmath>
#include <iostream>
#include "../pos.h"
#include "../diagnostic.h"

enum class DiagType
{
	ERROR,
	WARNING,
	NOTE,
	NORMAL
};

static unsigned nErrors = 0;
static bool newErrors = false;

namespace C4
{
	//===-------------------------------------------------------------------------
	//
	//	Append
	//
	//===-------------------------------------------------------------------------

	//
	// Declarations
	//
	
	static inline void append( std::string &str, Pos const &pos );
	static inline void append( std::string &str, std::string const &s );
	static inline void append( std::string &str, char const * const s );

  template< typename T >
  static void append( std::string &str, T t );
	
  template< typename T, typename... Args >
  static void append( std::string &str, T t, Args... args );
	
	//
	//	Definitions
	//
	
	static inline void append( std::string &str, Pos const &pos )
	{
		str += pos.name;
		str += ":";

		if ( pos.line )
		{
			append( str, pos.line );
			str += ":";
			if ( pos.column )
			{
				append( str, pos.column );
				str += ":";
			}
		}
    str += " ";
	}

	static inline void append( std::string &str, std::string const &s )
	{
		str += s;
	}

	static inline void append( std::string &str, char const * const s )
	{
		str += s;
	}

  template< typename T >
  static void append( std::string &str, T t )
  {
		str += std::to_string( t );
  }

  template< typename T, typename... Args >
  static void append( std::string &str, T t, Args... args )
  {
		append( str, t );
    append( str, args... );
  }

	//
	//	End append
	//

	inline unsigned ERRORS()
	{
		return nErrors;
	}

	inline bool NEW_ERRORS()
	{
		bool ret = newErrors;
		newErrors = false;
		return ret;
	}

  template< typename... Args >
  static void OUT( DiagType type, Pos const &pos, Args... args )
  {
		size_t posLength = 1; // :
		posLength += strlen( pos.name );
		if ( pos.line )
		{
			posLength += 1 + 1 /* : */ + log10l( pos.line );
			if ( pos.column )
				posLength += 1 + 1 /* : */ + log10l( pos.column );
		}

    std::string str = "";
		append( str, pos );
		++posLength;

		switch ( type )
		{
			case DiagType::ERROR:
        str += "ERROR ";
				posLength += 7; // length of "ERROR: "
				break;

			case DiagType::WARNING:
        str += "WARNING: ";
				posLength += 9; // length of "WARNING: "
				break;

			case DiagType::NOTE:
        str += "NOTE: ";
				posLength += 6; // length of "NOTE: "
				break;

			default:;
		}

		append( str, args... );

		/*
		 * Replace Newlines
		 */
		std::string newLine = "\n";
		newLine.replace( 1, 1, posLength, ' ' );

		size_t strPos = str.find( "\n" );
		while ( strPos != str.npos )
		{
			str.replace( strPos, 1, newLine );
			
			strPos = str.find( "\n", strPos + 1 );
		}
		// end replace Newlines

		std::cerr << str << std::endl;
  }

  template< typename... Args >
  void OUT( Pos const &pos, Args... args )
  {
		OUT( DiagType::NORMAL, pos, args... );
	}

  template< typename... Args >
  void ERROR( Pos const &pos, Args... args )
  {
		newErrors = true;
		++nErrors;

		OUT( DiagType::ERROR, pos, args... );
  }

  template< typename... Args >
  void WARNING( Pos const &pos, Args... args )
  {
		OUT( DiagType::WARNING, pos, args... );
  }

  template< typename... Args >
  void NOTE( Pos const &pos, Args... args )
  {
		OUT( DiagType::NOTE, pos, args... );
  }
}

#endif
