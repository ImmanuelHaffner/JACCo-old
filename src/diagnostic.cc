#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <errno.h>
#include <iostream>

#include "diagnostic.h"

static void verrorf(Pos const*, char const* fmt, va_list);

static unsigned nErrors   = 0;
static bool     newErrors = false;

void errorErrno(Pos const& pos)
{
	errorf(pos, "%s", strerror(errno));
}

void errorf(Pos const& pos, char const* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	verrorf(&pos, fmt, ap);
	va_end(ap);
}

void errorf(char const* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	verrorf(nullptr, fmt, ap);
	va_end(ap);
}

bool hasNewErrors()
{
	auto const res = newErrors;
	newErrors = false;
	return res;
}

int printDiagnosticSummary()
{
	if (nErrors != 0) {
    std::cerr << nErrors << " error(s)\n";
		return 1;
	}
	return 0;
}

static void verrorf(Pos const* const pos, char const* fmt, va_list ap)
{
	newErrors = true;
	++nErrors;

  std::ostream &out = std::cerr;

	if (pos) {
    out << pos->name << ":";
    if ( pos->line )
      out << pos->line << ":";
    if ( pos->column )
      out << pos->column << ":";
    out << " ";
	}
  out << "error: ";

	for (; auto f = strchr(fmt, '%'); fmt = f) {
    out.write( fmt, f - fmt );
		++f; // Skip '%'.
		switch (*f++) {
		case '%':
      out.put( '%' );
			break;

		case 'c': {
			auto const c = (char)va_arg(ap, int);
      out.put( c );
			break;
		}

		case 's': {
			auto const s = va_arg(ap, char const*);
      out << s;
			break;
		}

		default:
			PANIC("invalid format specifier");
		}
	}
  out << fmt;

  out.put( '\n' );
}
