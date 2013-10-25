//===--- CharUtils.h-------------------------------------------------------===//
//
//	~~~ The C4 Compiler ~~~
//
//	This file defines macros to handle chars.
//
//===----------------------------------------------------------------------===//

#ifndef CHAR_UTILS_H
#define CHAR_UTILS_H

#include <iostream>
#include <string>

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

inline bool isAlpha( char const chr )
{
	switch ( chr )
	{
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
		case 'f':
		case 'g':
		case 'h':
		case 'i':
		case 'j':
		case 'k':
		case 'l':
		case 'm':
		case 'n':
		case 'o':
		case 'p':
		case 'q':
		case 'r':
		case 's':
		case 't':
		case 'u':
		case 'v':
		case 'w':
		case 'x':
		case 'y':
		case 'z':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
			return true;
	}
	return false;
}

inline bool isDigit( char const chr )
{
	switch ( chr )
	{
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case '0':
			return true;
	}
	return false;
}

inline bool isAlphaNum( char const chr )
{
	return isAlpha( chr ) || isDigit( chr );
}

inline bool isNonDigit( char const chr )
{
	return isAlpha( chr ) || chr == '_';
}

inline char const * visualizeChar( char const chr )
{
	switch ( chr )
	{
		case '\?':
			return "\\?";
		case '\a':
			return "\\a";
		case '\b':
			return "\\b";
		case '\f':
			return "\\f";
		case '\n':
			return "\\n";
		case '\r':
			return "\\r";
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
