


















extern void __assert_fail (__const char *__assertion, __const char *__file,
      unsigned int __line, __const char *__function)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));


extern void __assert_perror_fail (int __errnum, __const char *__file,
      unsigned int __line,
      __const char *__function)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));




extern void __assert (const char *__assertion, const char *__file, int __line)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));



int my_ffs(unsigned x) { int i; if (x == 0) return 0; for (i = 0; i < 8 * sizeof (unsigned); i++) if (x & ((unsigned) 1 << i)) break; return i + 1; } int my_ctz(unsigned x) { int i; for (i = 0; i < 8 * sizeof (unsigned); i++) if (x & ((unsigned) 1 << i)) break; return i; } int my_clz(unsigned x) { int i; for (i = 0; i < 8 * sizeof (unsigned); i++) if (x & ((unsigned) 1 << ((8 * sizeof (unsigned)) - i - 1))) break; return i; } int my_clrsb(unsigned x) { int i; int leading = (x >> 8 * sizeof (unsigned) - 1) & 1; for (i = 1; i < 8 * sizeof (unsigned); i++) if (((x >> ((8 * sizeof (unsigned)) - i - 1)) & 1) != leading) break; return i - 1; } int my_popcount(unsigned x) { int i; int count = 0; for (i = 0; i < 8 * sizeof (unsigned); i++) if (x & ((unsigned) 1 << i)) count++; return count; } int my_parity(unsigned x) { int i; int count = 0; for (i = 0; i < 8 * sizeof (unsigned); i++) if (x & ((unsigned) 1 << i)) count++; return count & 1; };
int my_ffsl(unsigned long x) { int i; if (x == 0) return 0; for (i = 0; i < 8 * sizeof (unsigned long); i++) if (x & ((unsigned long) 1 << i)) break; return i + 1; } int my_ctzl(unsigned long x) { int i; for (i = 0; i < 8 * sizeof (unsigned long); i++) if (x & ((unsigned long) 1 << i)) break; return i; } int my_clzl(unsigned long x) { int i; for (i = 0; i < 8 * sizeof (unsigned long); i++) if (x & ((unsigned long) 1 << ((8 * sizeof (unsigned long)) - i - 1))) break; return i; } int my_clrsbl(unsigned long x) { int i; int leading = (x >> 8 * sizeof (unsigned long) - 1) & 1; for (i = 1; i < 8 * sizeof (unsigned long); i++) if (((x >> ((8 * sizeof (unsigned long)) - i - 1)) & 1) != leading) break; return i - 1; } int my_popcountl(unsigned long x) { int i; int count = 0; for (i = 0; i < 8 * sizeof (unsigned long); i++) if (x & ((unsigned long) 1 << i)) count++; return count; } int my_parityl(unsigned long x) { int i; int count = 0; for (i = 0; i < 8 * sizeof (unsigned long); i++) if (x & ((unsigned long) 1 << i)) count++; return count & 1; };
int my_ffsll(unsigned long long x) { int i; if (x == 0) return 0; for (i = 0; i < 8 * sizeof (unsigned long long); i++) if (x & ((unsigned long long) 1 << i)) break; return i + 1; } int my_ctzll(unsigned long long x) { int i; for (i = 0; i < 8 * sizeof (unsigned long long); i++) if (x & ((unsigned long long) 1 << i)) break; return i; } int my_clzll(unsigned long long x) { int i; for (i = 0; i < 8 * sizeof (unsigned long long); i++) if (x & ((unsigned long long) 1 << ((8 * sizeof (unsigned long long)) - i - 1))) break; return i; } int my_clrsbll(unsigned long long x) { int i; int leading = (x >> 8 * sizeof (unsigned long long) - 1) & 1; for (i = 1; i < 8 * sizeof (unsigned long long); i++) if (((x >> ((8 * sizeof (unsigned long long)) - i - 1)) & 1) != leading) break; return i - 1; } int my_popcountll(unsigned long long x) { int i; int count = 0; for (i = 0; i < 8 * sizeof (unsigned long long); i++) if (x & ((unsigned long long) 1 << i)) count++; return count; } int my_parityll(unsigned long long x) { int i; int count = 0; for (i = 0; i < 8 * sizeof (unsigned long long); i++) if (x & ((unsigned long long) 1 << i)) count++; return count & 1; };

extern void abort (void);
extern void exit (int);
unsigned int ints[] =



{ 0x00000000UL, 0x00000001UL, 0x80000000UL, 0x00000002UL, 0x40000000UL, 0x00010000UL, 0x00008000UL, 0xa5a5a5a5UL, 0x5a5a5a5aUL, 0xcafe0000UL, 0x00cafe00UL, 0x0000cafeUL, 0xffffffffUL };




unsigned long longs[] =

{ 0x0000000000000000ULL, 0x0000000000000001ULL, 0x8000000000000000ULL, 0x0000000000000002ULL, 0x4000000000000000ULL, 0x0000000100000000ULL, 0x0000000080000000ULL, 0xa5a5a5a5a5a5a5a5ULL, 0x5a5a5a5a5a5a5a5aULL, 0xcafecafe00000000ULL, 0x0000cafecafe0000ULL, 0x00000000cafecafeULL, 0xffffffffffffffffULL };




unsigned long long longlongs[] =

{ 0x0000000000000000ULL, 0x0000000000000001ULL, 0x8000000000000000ULL, 0x0000000000000002ULL, 0x4000000000000000ULL, 0x0000000100000000ULL, 0x0000000080000000ULL, 0xa5a5a5a5a5a5a5a5ULL, 0x5a5a5a5a5a5a5a5aULL, 0xcafecafe00000000ULL, 0x0000cafecafe0000ULL, 0x00000000cafecafeULL, 0xffffffffffffffffULL };






int
main (void)
{
  int i;

  for (i = 0; i < (sizeof (ints) / sizeof (ints[0])); i++)
    {
      if (__builtin_ffs (ints[i]) != my_ffs (ints[i]))
 abort ();
      if (ints[i] != 0
   && __builtin_clz (ints[i]) != my_clz (ints[i]))
 abort ();
      if (ints[i] != 0
   && __builtin_ctz (ints[i]) != my_ctz (ints[i]))
 abort ();
      if (__builtin_clrsb (ints[i]) != my_clrsb (ints[i]))
 abort ();
      if (__builtin_popcount (ints[i]) != my_popcount (ints[i]))
 abort ();
      if (__builtin_parity (ints[i]) != my_parity (ints[i]))
 abort ();
    }

  for (i = 0; i < (sizeof (longs) / sizeof (longs[0])); i++)
    {
      if (__builtin_ffsl (longs[i]) != my_ffsl (longs[i]))
 abort ();
      if (longs[i] != 0
   && __builtin_clzl (longs[i]) != my_clzl (longs[i]))
 abort ();
      if (longs[i] != 0
   && __builtin_ctzl (longs[i]) != my_ctzl (longs[i]))
 abort ();
      if (__builtin_clrsbl (longs[i]) != my_clrsbl (longs[i]))
 abort ();
      if (__builtin_popcountl (longs[i]) != my_popcountl (longs[i]))
 abort ();
      if (__builtin_parityl (longs[i]) != my_parityl (longs[i]))
 abort ();
    }

  for (i = 0; i < (sizeof (longlongs) / sizeof (longlongs[0])); i++)
    {
      if (__builtin_ffsll (longlongs[i]) != my_ffsll (longlongs[i]))
 abort ();
      if (longlongs[i] != 0
   && __builtin_clzll (longlongs[i]) != my_clzll (longlongs[i]))
 abort ();
      if (longlongs[i] != 0
   && __builtin_ctzll (longlongs[i]) != my_ctzll (longlongs[i]))
 abort ();
      if (__builtin_clrsbll (longlongs[i]) != my_clrsbll (longlongs[i]))
 abort ();
      if (__builtin_popcountll (longlongs[i]) != my_popcountll (longlongs[i]))
 abort ();
      if (__builtin_parityll (longlongs[i]) != my_parityll (longlongs[i]))
 abort ();
    }
  if (__builtin_ffs (0x00000000UL) != my_ffs (0x00000000UL)) abort (); if (0x00000000UL != 0 && __builtin_clz (0x00000000UL) != my_clz (0x00000000UL)) abort (); if (0x00000000UL != 0 && __builtin_ctz (0x00000000UL) != my_ctz (0x00000000UL)) abort (); if (__builtin_clrsb (0x00000000UL) != my_clrsb (0x00000000UL)) abort (); if (__builtin_popcount (0x00000000UL) != my_popcount (0x00000000UL)) abort (); if (__builtin_parity (0x00000000UL) != my_parity (0x00000000UL)) abort ();;
  if (__builtin_ffs (0x00000001UL) != my_ffs (0x00000001UL)) abort (); if (0x00000001UL != 0 && __builtin_clz (0x00000001UL) != my_clz (0x00000001UL)) abort (); if (0x00000001UL != 0 && __builtin_ctz (0x00000001UL) != my_ctz (0x00000001UL)) abort (); if (__builtin_clrsb (0x00000001UL) != my_clrsb (0x00000001UL)) abort (); if (__builtin_popcount (0x00000001UL) != my_popcount (0x00000001UL)) abort (); if (__builtin_parity (0x00000001UL) != my_parity (0x00000001UL)) abort ();;
  if (__builtin_ffs (0x80000000UL) != my_ffs (0x80000000UL)) abort (); if (0x80000000UL != 0 && __builtin_clz (0x80000000UL) != my_clz (0x80000000UL)) abort (); if (0x80000000UL != 0 && __builtin_ctz (0x80000000UL) != my_ctz (0x80000000UL)) abort (); if (__builtin_clrsb (0x80000000UL) != my_clrsb (0x80000000UL)) abort (); if (__builtin_popcount (0x80000000UL) != my_popcount (0x80000000UL)) abort (); if (__builtin_parity (0x80000000UL) != my_parity (0x80000000UL)) abort ();;
  if (__builtin_ffs (0x40000000UL) != my_ffs (0x40000000UL)) abort (); if (0x40000000UL != 0 && __builtin_clz (0x40000000UL) != my_clz (0x40000000UL)) abort (); if (0x40000000UL != 0 && __builtin_ctz (0x40000000UL) != my_ctz (0x40000000UL)) abort (); if (__builtin_clrsb (0x40000000UL) != my_clrsb (0x40000000UL)) abort (); if (__builtin_popcount (0x40000000UL) != my_popcount (0x40000000UL)) abort (); if (__builtin_parity (0x40000000UL) != my_parity (0x40000000UL)) abort ();;
  if (__builtin_ffs (0x00010000UL) != my_ffs (0x00010000UL)) abort (); if (0x00010000UL != 0 && __builtin_clz (0x00010000UL) != my_clz (0x00010000UL)) abort (); if (0x00010000UL != 0 && __builtin_ctz (0x00010000UL) != my_ctz (0x00010000UL)) abort (); if (__builtin_clrsb (0x00010000UL) != my_clrsb (0x00010000UL)) abort (); if (__builtin_popcount (0x00010000UL) != my_popcount (0x00010000UL)) abort (); if (__builtin_parity (0x00010000UL) != my_parity (0x00010000UL)) abort ();;
  if (__builtin_ffs (0x00008000UL) != my_ffs (0x00008000UL)) abort (); if (0x00008000UL != 0 && __builtin_clz (0x00008000UL) != my_clz (0x00008000UL)) abort (); if (0x00008000UL != 0 && __builtin_ctz (0x00008000UL) != my_ctz (0x00008000UL)) abort (); if (__builtin_clrsb (0x00008000UL) != my_clrsb (0x00008000UL)) abort (); if (__builtin_popcount (0x00008000UL) != my_popcount (0x00008000UL)) abort (); if (__builtin_parity (0x00008000UL) != my_parity (0x00008000UL)) abort ();;
  if (__builtin_ffs (0xa5a5a5a5UL) != my_ffs (0xa5a5a5a5UL)) abort (); if (0xa5a5a5a5UL != 0 && __builtin_clz (0xa5a5a5a5UL) != my_clz (0xa5a5a5a5UL)) abort (); if (0xa5a5a5a5UL != 0 && __builtin_ctz (0xa5a5a5a5UL) != my_ctz (0xa5a5a5a5UL)) abort (); if (__builtin_clrsb (0xa5a5a5a5UL) != my_clrsb (0xa5a5a5a5UL)) abort (); if (__builtin_popcount (0xa5a5a5a5UL) != my_popcount (0xa5a5a5a5UL)) abort (); if (__builtin_parity (0xa5a5a5a5UL) != my_parity (0xa5a5a5a5UL)) abort ();;
  if (__builtin_ffs (0x5a5a5a5aUL) != my_ffs (0x5a5a5a5aUL)) abort (); if (0x5a5a5a5aUL != 0 && __builtin_clz (0x5a5a5a5aUL) != my_clz (0x5a5a5a5aUL)) abort (); if (0x5a5a5a5aUL != 0 && __builtin_ctz (0x5a5a5a5aUL) != my_ctz (0x5a5a5a5aUL)) abort (); if (__builtin_clrsb (0x5a5a5a5aUL) != my_clrsb (0x5a5a5a5aUL)) abort (); if (__builtin_popcount (0x5a5a5a5aUL) != my_popcount (0x5a5a5a5aUL)) abort (); if (__builtin_parity (0x5a5a5a5aUL) != my_parity (0x5a5a5a5aUL)) abort ();;
  if (__builtin_ffs (0xcafe0000UL) != my_ffs (0xcafe0000UL)) abort (); if (0xcafe0000UL != 0 && __builtin_clz (0xcafe0000UL) != my_clz (0xcafe0000UL)) abort (); if (0xcafe0000UL != 0 && __builtin_ctz (0xcafe0000UL) != my_ctz (0xcafe0000UL)) abort (); if (__builtin_clrsb (0xcafe0000UL) != my_clrsb (0xcafe0000UL)) abort (); if (__builtin_popcount (0xcafe0000UL) != my_popcount (0xcafe0000UL)) abort (); if (__builtin_parity (0xcafe0000UL) != my_parity (0xcafe0000UL)) abort ();;
  if (__builtin_ffs (0x00cafe00UL) != my_ffs (0x00cafe00UL)) abort (); if (0x00cafe00UL != 0 && __builtin_clz (0x00cafe00UL) != my_clz (0x00cafe00UL)) abort (); if (0x00cafe00UL != 0 && __builtin_ctz (0x00cafe00UL) != my_ctz (0x00cafe00UL)) abort (); if (__builtin_clrsb (0x00cafe00UL) != my_clrsb (0x00cafe00UL)) abort (); if (__builtin_popcount (0x00cafe00UL) != my_popcount (0x00cafe00UL)) abort (); if (__builtin_parity (0x00cafe00UL) != my_parity (0x00cafe00UL)) abort ();;
  if (__builtin_ffs (0x0000cafeUL) != my_ffs (0x0000cafeUL)) abort (); if (0x0000cafeUL != 0 && __builtin_clz (0x0000cafeUL) != my_clz (0x0000cafeUL)) abort (); if (0x0000cafeUL != 0 && __builtin_ctz (0x0000cafeUL) != my_ctz (0x0000cafeUL)) abort (); if (__builtin_clrsb (0x0000cafeUL) != my_clrsb (0x0000cafeUL)) abort (); if (__builtin_popcount (0x0000cafeUL) != my_popcount (0x0000cafeUL)) abort (); if (__builtin_parity (0x0000cafeUL) != my_parity (0x0000cafeUL)) abort ();;
  if (__builtin_ffs (0xffffffffUL) != my_ffs (0xffffffffUL)) abort (); if (0xffffffffUL != 0 && __builtin_clz (0xffffffffUL) != my_clz (0xffffffffUL)) abort (); if (0xffffffffUL != 0 && __builtin_ctz (0xffffffffUL) != my_ctz (0xffffffffUL)) abort (); if (__builtin_clrsb (0xffffffffUL) != my_clrsb (0xffffffffUL)) abort (); if (__builtin_popcount (0xffffffffUL) != my_popcount (0xffffffffUL)) abort (); if (__builtin_parity (0xffffffffUL) != my_parity (0xffffffffUL)) abort ();;



  if (__builtin_ffsll (0x0000000000000000ULL) != my_ffsll (0x0000000000000000ULL)) abort (); if (0x0000000000000000ULL != 0 && __builtin_clzll (0x0000000000000000ULL) != my_clzll (0x0000000000000000ULL)) abort (); if (0x0000000000000000ULL != 0 && __builtin_ctzll (0x0000000000000000ULL) != my_ctzll (0x0000000000000000ULL)) abort (); if (__builtin_clrsbll (0x0000000000000000ULL) != my_clrsbll (0x0000000000000000ULL)) abort (); if (__builtin_popcountll (0x0000000000000000ULL) != my_popcountll (0x0000000000000000ULL)) abort (); if (__builtin_parityll (0x0000000000000000ULL) != my_parityll (0x0000000000000000ULL)) abort ();;
  if (__builtin_ffsll (0x0000000000000001ULL) != my_ffsll (0x0000000000000001ULL)) abort (); if (0x0000000000000001ULL != 0 && __builtin_clzll (0x0000000000000001ULL) != my_clzll (0x0000000000000001ULL)) abort (); if (0x0000000000000001ULL != 0 && __builtin_ctzll (0x0000000000000001ULL) != my_ctzll (0x0000000000000001ULL)) abort (); if (__builtin_clrsbll (0x0000000000000001ULL) != my_clrsbll (0x0000000000000001ULL)) abort (); if (__builtin_popcountll (0x0000000000000001ULL) != my_popcountll (0x0000000000000001ULL)) abort (); if (__builtin_parityll (0x0000000000000001ULL) != my_parityll (0x0000000000000001ULL)) abort ();;
  if (__builtin_ffsll (0x8000000000000000ULL) != my_ffsll (0x8000000000000000ULL)) abort (); if (0x8000000000000000ULL != 0 && __builtin_clzll (0x8000000000000000ULL) != my_clzll (0x8000000000000000ULL)) abort (); if (0x8000000000000000ULL != 0 && __builtin_ctzll (0x8000000000000000ULL) != my_ctzll (0x8000000000000000ULL)) abort (); if (__builtin_clrsbll (0x8000000000000000ULL) != my_clrsbll (0x8000000000000000ULL)) abort (); if (__builtin_popcountll (0x8000000000000000ULL) != my_popcountll (0x8000000000000000ULL)) abort (); if (__builtin_parityll (0x8000000000000000ULL) != my_parityll (0x8000000000000000ULL)) abort ();;
  if (__builtin_ffsll (0x0000000000000002ULL) != my_ffsll (0x0000000000000002ULL)) abort (); if (0x0000000000000002ULL != 0 && __builtin_clzll (0x0000000000000002ULL) != my_clzll (0x0000000000000002ULL)) abort (); if (0x0000000000000002ULL != 0 && __builtin_ctzll (0x0000000000000002ULL) != my_ctzll (0x0000000000000002ULL)) abort (); if (__builtin_clrsbll (0x0000000000000002ULL) != my_clrsbll (0x0000000000000002ULL)) abort (); if (__builtin_popcountll (0x0000000000000002ULL) != my_popcountll (0x0000000000000002ULL)) abort (); if (__builtin_parityll (0x0000000000000002ULL) != my_parityll (0x0000000000000002ULL)) abort ();;
  if (__builtin_ffsll (0x4000000000000000ULL) != my_ffsll (0x4000000000000000ULL)) abort (); if (0x4000000000000000ULL != 0 && __builtin_clzll (0x4000000000000000ULL) != my_clzll (0x4000000000000000ULL)) abort (); if (0x4000000000000000ULL != 0 && __builtin_ctzll (0x4000000000000000ULL) != my_ctzll (0x4000000000000000ULL)) abort (); if (__builtin_clrsbll (0x4000000000000000ULL) != my_clrsbll (0x4000000000000000ULL)) abort (); if (__builtin_popcountll (0x4000000000000000ULL) != my_popcountll (0x4000000000000000ULL)) abort (); if (__builtin_parityll (0x4000000000000000ULL) != my_parityll (0x4000000000000000ULL)) abort ();;
  if (__builtin_ffsll (0x0000000100000000ULL) != my_ffsll (0x0000000100000000ULL)) abort (); if (0x0000000100000000ULL != 0 && __builtin_clzll (0x0000000100000000ULL) != my_clzll (0x0000000100000000ULL)) abort (); if (0x0000000100000000ULL != 0 && __builtin_ctzll (0x0000000100000000ULL) != my_ctzll (0x0000000100000000ULL)) abort (); if (__builtin_clrsbll (0x0000000100000000ULL) != my_clrsbll (0x0000000100000000ULL)) abort (); if (__builtin_popcountll (0x0000000100000000ULL) != my_popcountll (0x0000000100000000ULL)) abort (); if (__builtin_parityll (0x0000000100000000ULL) != my_parityll (0x0000000100000000ULL)) abort ();;
  if (__builtin_ffsll (0x0000000080000000ULL) != my_ffsll (0x0000000080000000ULL)) abort (); if (0x0000000080000000ULL != 0 && __builtin_clzll (0x0000000080000000ULL) != my_clzll (0x0000000080000000ULL)) abort (); if (0x0000000080000000ULL != 0 && __builtin_ctzll (0x0000000080000000ULL) != my_ctzll (0x0000000080000000ULL)) abort (); if (__builtin_clrsbll (0x0000000080000000ULL) != my_clrsbll (0x0000000080000000ULL)) abort (); if (__builtin_popcountll (0x0000000080000000ULL) != my_popcountll (0x0000000080000000ULL)) abort (); if (__builtin_parityll (0x0000000080000000ULL) != my_parityll (0x0000000080000000ULL)) abort ();;
  if (__builtin_ffsll (0xa5a5a5a5a5a5a5a5ULL) != my_ffsll (0xa5a5a5a5a5a5a5a5ULL)) abort (); if (0xa5a5a5a5a5a5a5a5ULL != 0 && __builtin_clzll (0xa5a5a5a5a5a5a5a5ULL) != my_clzll (0xa5a5a5a5a5a5a5a5ULL)) abort (); if (0xa5a5a5a5a5a5a5a5ULL != 0 && __builtin_ctzll (0xa5a5a5a5a5a5a5a5ULL) != my_ctzll (0xa5a5a5a5a5a5a5a5ULL)) abort (); if (__builtin_clrsbll (0xa5a5a5a5a5a5a5a5ULL) != my_clrsbll (0xa5a5a5a5a5a5a5a5ULL)) abort (); if (__builtin_popcountll (0xa5a5a5a5a5a5a5a5ULL) != my_popcountll (0xa5a5a5a5a5a5a5a5ULL)) abort (); if (__builtin_parityll (0xa5a5a5a5a5a5a5a5ULL) != my_parityll (0xa5a5a5a5a5a5a5a5ULL)) abort ();;
  if (__builtin_ffsll (0x5a5a5a5a5a5a5a5aULL) != my_ffsll (0x5a5a5a5a5a5a5a5aULL)) abort (); if (0x5a5a5a5a5a5a5a5aULL != 0 && __builtin_clzll (0x5a5a5a5a5a5a5a5aULL) != my_clzll (0x5a5a5a5a5a5a5a5aULL)) abort (); if (0x5a5a5a5a5a5a5a5aULL != 0 && __builtin_ctzll (0x5a5a5a5a5a5a5a5aULL) != my_ctzll (0x5a5a5a5a5a5a5a5aULL)) abort (); if (__builtin_clrsbll (0x5a5a5a5a5a5a5a5aULL) != my_clrsbll (0x5a5a5a5a5a5a5a5aULL)) abort (); if (__builtin_popcountll (0x5a5a5a5a5a5a5a5aULL) != my_popcountll (0x5a5a5a5a5a5a5a5aULL)) abort (); if (__builtin_parityll (0x5a5a5a5a5a5a5a5aULL) != my_parityll (0x5a5a5a5a5a5a5a5aULL)) abort ();;
  if (__builtin_ffsll (0xcafecafe00000000ULL) != my_ffsll (0xcafecafe00000000ULL)) abort (); if (0xcafecafe00000000ULL != 0 && __builtin_clzll (0xcafecafe00000000ULL) != my_clzll (0xcafecafe00000000ULL)) abort (); if (0xcafecafe00000000ULL != 0 && __builtin_ctzll (0xcafecafe00000000ULL) != my_ctzll (0xcafecafe00000000ULL)) abort (); if (__builtin_clrsbll (0xcafecafe00000000ULL) != my_clrsbll (0xcafecafe00000000ULL)) abort (); if (__builtin_popcountll (0xcafecafe00000000ULL) != my_popcountll (0xcafecafe00000000ULL)) abort (); if (__builtin_parityll (0xcafecafe00000000ULL) != my_parityll (0xcafecafe00000000ULL)) abort ();;
  if (__builtin_ffsll (0x0000cafecafe0000ULL) != my_ffsll (0x0000cafecafe0000ULL)) abort (); if (0x0000cafecafe0000ULL != 0 && __builtin_clzll (0x0000cafecafe0000ULL) != my_clzll (0x0000cafecafe0000ULL)) abort (); if (0x0000cafecafe0000ULL != 0 && __builtin_ctzll (0x0000cafecafe0000ULL) != my_ctzll (0x0000cafecafe0000ULL)) abort (); if (__builtin_clrsbll (0x0000cafecafe0000ULL) != my_clrsbll (0x0000cafecafe0000ULL)) abort (); if (__builtin_popcountll (0x0000cafecafe0000ULL) != my_popcountll (0x0000cafecafe0000ULL)) abort (); if (__builtin_parityll (0x0000cafecafe0000ULL) != my_parityll (0x0000cafecafe0000ULL)) abort ();;
  if (__builtin_ffsll (0x00000000cafecafeULL) != my_ffsll (0x00000000cafecafeULL)) abort (); if (0x00000000cafecafeULL != 0 && __builtin_clzll (0x00000000cafecafeULL) != my_clzll (0x00000000cafecafeULL)) abort (); if (0x00000000cafecafeULL != 0 && __builtin_ctzll (0x00000000cafecafeULL) != my_ctzll (0x00000000cafecafeULL)) abort (); if (__builtin_clrsbll (0x00000000cafecafeULL) != my_clrsbll (0x00000000cafecafeULL)) abort (); if (__builtin_popcountll (0x00000000cafecafeULL) != my_popcountll (0x00000000cafecafeULL)) abort (); if (__builtin_parityll (0x00000000cafecafeULL) != my_parityll (0x00000000cafecafeULL)) abort ();;
  if (__builtin_ffsll (0xffffffffffffffffULL) != my_ffsll (0xffffffffffffffffULL)) abort (); if (0xffffffffffffffffULL != 0 && __builtin_clzll (0xffffffffffffffffULL) != my_clzll (0xffffffffffffffffULL)) abort (); if (0xffffffffffffffffULL != 0 && __builtin_ctzll (0xffffffffffffffffULL) != my_ctzll (0xffffffffffffffffULL)) abort (); if (__builtin_clrsbll (0xffffffffffffffffULL) != my_clrsbll (0xffffffffffffffffULL)) abort (); if (__builtin_popcountll (0xffffffffffffffffULL) != my_popcountll (0xffffffffffffffffULL)) abort (); if (__builtin_parityll (0xffffffffffffffffULL) != my_parityll (0xffffffffffffffffULL)) abort ();;


  exit (0);
}
