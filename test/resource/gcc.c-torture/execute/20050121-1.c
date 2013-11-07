

extern void abort ();
typedef long double ldouble_t;
typedef long long llong;

__attribute__((pure)) _Complex float foo_float (int x) { _Complex float r; __real r = x + 1; __imag r = x - 1; return r; } void bar_float (float *x) { *x = __real foo_float (5); } void baz_float (float *x) { *x = __imag foo_float (5); }
__attribute__((pure)) _Complex double foo_double (int x) { _Complex double r; __real r = x + 1; __imag r = x - 1; return r; } void bar_double (double *x) { *x = __real foo_double (5); } void baz_double (double *x) { *x = __imag foo_double (5); }
__attribute__((pure)) _Complex long double foo_ldouble_t (int x) { _Complex long double r; __real r = x + 1; __imag r = x - 1; return r; } void bar_ldouble_t (long double *x) { *x = __real foo_ldouble_t (5); } void baz_ldouble_t (long double *x) { *x = __imag foo_ldouble_t (5); }
__attribute__((pure)) _Complex char foo_char (int x) { _Complex char r; __real r = x + 1; __imag r = x - 1; return r; } void bar_char (char *x) { *x = __real foo_char (5); } void baz_char (char *x) { *x = __imag foo_char (5); }
__attribute__((pure)) _Complex short foo_short (int x) { _Complex short r; __real r = x + 1; __imag r = x - 1; return r; } void bar_short (short *x) { *x = __real foo_short (5); } void baz_short (short *x) { *x = __imag foo_short (5); }
__attribute__((pure)) _Complex int foo_int (int x) { _Complex int r; __real r = x + 1; __imag r = x - 1; return r; } void bar_int (int *x) { *x = __real foo_int (5); } void baz_int (int *x) { *x = __imag foo_int (5); }
__attribute__((pure)) _Complex long foo_long (int x) { _Complex long r; __real r = x + 1; __imag r = x - 1; return r; } void bar_long (long *x) { *x = __real foo_long (5); } void baz_long (long *x) { *x = __imag foo_long (5); }
__attribute__((pure)) _Complex long long foo_llong (int x) { _Complex long long r; __real r = x + 1; __imag r = x - 1; return r; } void bar_llong (long long *x) { *x = __real foo_llong (5); } void baz_llong (long long *x) { *x = __imag foo_llong (5); }


int
main (void)
{
  { float var = 0; bar_float (&var); if (var != 6) abort (); var = 0; baz_float (&var); if (var != 4) abort (); }
  { double var = 0; bar_double (&var); if (var != 6) abort (); var = 0; baz_double (&var); if (var != 4) abort (); }
  { long double var = 0; bar_ldouble_t (&var); if (var != 6) abort (); var = 0; baz_ldouble_t (&var); if (var != 4) abort (); }
  { char var = 0; bar_char (&var); if (var != 6) abort (); var = 0; baz_char (&var); if (var != 4) abort (); }
  { short var = 0; bar_short (&var); if (var != 6) abort (); var = 0; baz_short (&var); if (var != 4) abort (); }
  { int var = 0; bar_int (&var); if (var != 6) abort (); var = 0; baz_int (&var); if (var != 4) abort (); }
  { long var = 0; bar_long (&var); if (var != 6) abort (); var = 0; baz_long (&var); if (var != 4) abort (); }
  { long long var = 0; bar_llong (&var); if (var != 6) abort (); var = 0; baz_llong (&var); if (var != 4) abort (); }
  return 0;
}
