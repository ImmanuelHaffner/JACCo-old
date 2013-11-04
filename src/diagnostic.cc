#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <errno.h>

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
		fprintf(stderr, "%u error(s)\n", nErrors);
		return 1;
	}
	return 0;
}

static void verrorf(Pos const* const pos, char const* fmt, va_list ap)
{
	newErrors = true;
	++nErrors;

	auto const out = stderr;

	if (pos) {
		if (pos->line && pos->column) {
			fprintf(out, "%s:%u:%u: ", pos->name, pos->line, pos->column);
		} else if (pos->line) {
			fprintf(out, "%s:%u: ", pos->name, pos->line);
		} else if (pos->column) {
			fprintf(out, "%s:%u: ", pos->name, pos->column);
		} else {
			fprintf(out, "%s: ", pos->name);
		}
	}
	fputs("error: ", out);

	for (; auto f = strchr(fmt, '%'); fmt = f) {
		fwrite(fmt, 1, f - fmt, out);
		++f; // Skip '%'.
		switch (*f++) {
		case '%':
			fputc('%', out);
			break;

		case 'c': {
			auto const c = (char)va_arg(ap, int);
			fputc(c, out);
			break;
		}

		case 's': {
			auto const s = va_arg(ap, char const*);
			fputs(s, out);
			break;
		}

		default:
			PANIC("invalid format specifier");
		}
	}
	fputs(fmt, out);

	fputc('\n', out);
}
