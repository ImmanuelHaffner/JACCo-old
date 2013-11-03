




int failures;

int foo32 (_Decimal32 z)
{
  z = z + 1.0df;
}

int foo64 (_Decimal64 z)
{
  z = z + 1.0dd;
}

int foo128 (_Decimal128 z)
{
  z = z + 1.0dl;
}

int
main ()
{
  _Decimal32 d32 = 1.1df;
  _Decimal64 d64 = 1.2dd;
  _Decimal128 d128 = 1.3dl;

  foo32 (d32);
  if (d32 != 1.1df)
    __builtin_abort ();

  foo64 (d64);
  if (d64 != 1.2dd)
    __builtin_abort ();

  foo128 (d128);
  if (d128 != 1.3dl)
    __builtin_abort ();

  return 0;
}
