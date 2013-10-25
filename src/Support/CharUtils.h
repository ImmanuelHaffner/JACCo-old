//===--- CharUtils.h-------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines macros to handle chars.
//
//===----------------------------------------------------------------------===//

#ifndef CHAR_UTILS_H
#define CHAR_UTILS_H

inline bool isWhiteSpace( char const chr )
{
	switch ( chr )
	{
		case ' ':
		case '\n':
		case '\t':
		case '\v':
			return true;
	}
	return false;
}

inline bool isNewLine( char const chr )
{
	switch ( chr )
	{
		case '\n':
			return true;
	}
	return false;
}

inline char const * visualizeChar( char const chr )
{
	switch ( chr )
	{
		case '\n':
			return "\\n";
		case '\t':
			return "\\t";
		case '\v':
			return "\\v";
		case '\0':
			return "\\0";
	}
	char * ret = new char[2];
	ret[0] = chr; ret[1] = '\0';
	return ret;
}

#endif
