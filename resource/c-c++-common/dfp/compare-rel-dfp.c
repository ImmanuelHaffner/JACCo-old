




int failures;

_Decimal32 d32;
_Decimal64 d64;
_Decimal128 d128;


typedef _Decimal32 SDtype;
typedef _Decimal64 DDtype;
typedef _Decimal128 TDtype;

SDtype d32b;
DDtype d64b;
TDtype d128b;

void
inits (void)
{
  d32 = 1.0df;
  d64 = 3.0dd;
  d128 = 5.0dl;
  d32b = -1.0df;
  d64b = -4.0dd;
  d128b = -6.0dl;
}

void
compare_dfp (void)
{
  if ((d32 > d64) != 0) __builtin_abort ();
  if ((d32 >= d128b) != 1) __builtin_abort ();

  if ((d64 < d32) != 0) __builtin_abort ();
  if ((d64 <= d128) != 1) __builtin_abort ();

  if ((d128 > d32) != 1) __builtin_abort ();
  if ((d128 >= d64) != 1) __builtin_abort ();
}

int
main ()
{
  inits ();

  compare_dfp ();

  return 0;
}
