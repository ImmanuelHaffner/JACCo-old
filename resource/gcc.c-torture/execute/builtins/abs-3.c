


















typedef long int intmax_t;


extern void abort (void);
extern void link_error (void);

void
main_test (void)
{


  volatile int i0 = 0, i1 = 1, im1 = -1, imin = -2147483647, imax = 2147483647;
  volatile long l0 = 0L, l1 = 1L, lm1 = -1L, lmin = -9223372036854775807L, lmax = 9223372036854775807L;
  volatile long long ll0 = 0LL, ll1 = 1LL, llm1 = -1LL;
  volatile long long llmin = -9223372036854775807LL, llmax = 9223372036854775807LL;
  volatile intmax_t imax0 = 0, imax1 = 1, imaxm1 = -1;
  volatile intmax_t imaxmin = -9223372036854775807L, imaxmax = 9223372036854775807L;
  if (__builtin_abs (i0) != 0)
    abort ();
  if (__builtin_abs (0) != 0)
    link_error ();
  if (__builtin_abs (i1) != 1)
    abort ();
  if (__builtin_abs (1) != 1)
    link_error ();
  if (__builtin_abs (im1) != 1)
    abort ();
  if (__builtin_abs (-1) != 1)
    link_error ();
  if (__builtin_abs (imin) != 2147483647)
    abort ();
  if (__builtin_abs (-2147483647) != 2147483647)
    link_error ();
  if (__builtin_abs (imax) != 2147483647)
    abort ();
  if (__builtin_abs (2147483647) != 2147483647)
    link_error ();
  if (__builtin_labs (l0) != 0L)
    abort ();
  if (__builtin_labs (0L) != 0L)
    link_error ();
  if (__builtin_labs (l1) != 1L)
    abort ();
  if (__builtin_labs (1L) != 1L)
    link_error ();
  if (__builtin_labs (lm1) != 1L)
    abort ();
  if (__builtin_labs (-1L) != 1L)
    link_error ();
  if (__builtin_labs (lmin) != 9223372036854775807L)
    abort ();
  if (__builtin_labs (-9223372036854775807L) != 9223372036854775807L)
    link_error ();
  if (__builtin_labs (lmax) != 9223372036854775807L)
    abort ();
  if (__builtin_labs (9223372036854775807L) != 9223372036854775807L)
    link_error ();
  if (__builtin_llabs (ll0) != 0LL)
    abort ();
  if (__builtin_llabs (0LL) != 0LL)
    link_error ();
  if (__builtin_llabs (ll1) != 1LL)
    abort ();
  if (__builtin_llabs (1LL) != 1LL)
    link_error ();
  if (__builtin_llabs (llm1) != 1LL)
    abort ();
  if (__builtin_llabs (-1LL) != 1LL)
    link_error ();
  if (__builtin_llabs (llmin) != 9223372036854775807LL)
    abort ();
  if (__builtin_llabs (-9223372036854775807LL) != 9223372036854775807LL)
    link_error ();
  if (__builtin_llabs (llmax) != 9223372036854775807LL)
    abort ();
  if (__builtin_llabs (9223372036854775807LL) != 9223372036854775807LL)
    link_error ();
  if (__builtin_imaxabs (imax0) != 0)
    abort ();
  if (__builtin_imaxabs (0) != 0)
    link_error ();
  if (__builtin_imaxabs (imax1) != 1)
    abort ();
  if (__builtin_imaxabs (1) != 1)
    link_error ();
  if (__builtin_imaxabs (imaxm1) != 1)
    abort ();
  if (__builtin_imaxabs (-1) != 1)
    link_error ();
  if (__builtin_imaxabs (imaxmin) != 9223372036854775807L)
    abort ();
  if (__builtin_imaxabs (-9223372036854775807L) != 9223372036854775807L)
    link_error ();
  if (__builtin_imaxabs (imaxmax) != 9223372036854775807L)
    abort ();
  if (__builtin_imaxabs (9223372036854775807L) != 9223372036854775807L)
    link_error ();
}
