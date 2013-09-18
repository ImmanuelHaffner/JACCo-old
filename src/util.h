#ifndef UTIL_H
#define UTIL_H

#include <cassert>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

typedef uint8_t  u1;
typedef uint16_t u2;
typedef uint32_t u4;
typedef uint64_t u8;

template<typename T> inline T* nonNull(T* const p)
{
	assert(p);
	return p;
}

[[noreturn]] static inline void panic(char const* const file, int const line, char const* const msg)
{
	fprintf(stderr, "%s:%d: %s\n", file, line, msg);
	abort();
}

#define PANIC(msg) panic(__FILE__, __LINE__, (msg))

static inline bool strEq(char const* const a, char const* const b)
{
	return strcmp(a, b) == 0;
}

#endif
