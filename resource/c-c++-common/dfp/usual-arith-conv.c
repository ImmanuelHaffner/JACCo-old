int failures;

volatile _Decimal32 d32a, d32b, d32c;
volatile _Decimal64 d64a, d64b, d64c;
volatile _Decimal128 d128a, d128b, d128c;
volatile int i;

void
init ()
{
  d32b = 123.456e94df;
  d64b = 12.3456789012345e383dd;
  d128b = 12345.6789012345678901e4000dl;

  d32c = 1.3df;
  d64c = 1.2dd;
  d128c = 1.1dl;

  i = 2;
}

int
main ()
{
  init ();


  d128a = d128b + d32b;
  if (d128a < d128b)
    __builtin_abort ();
  d128a = d32b + d128b;
  if (d128a < d128b)
    __builtin_abort ();
  d128a = d128b + d64b;
  if (d128a < d128b)
    __builtin_abort ();
  d128a = d64b + d128b;
  if (d128a < d128b)
    __builtin_abort ();
  d64a = d64b + d32b;
  if (d64a < d64b)
    __builtin_abort ();
  d64a = d32b + d64b;
  if (d64a < d64b)
    __builtin_abort ();



  d128a = d128b * d32c;
  if (d128a < d128b)
    __builtin_abort ();
  d128a = d32c * d128b;
  if (d128a < d128b)
    __builtin_abort ();
  d128a = d128b * d64c;
  if (d128a < d128b)
    __builtin_abort ();
  d128a = d64c * d128b;
  if (d128a < d128b)
    __builtin_abort ();
  d64a = d64b * d32c;
  if (d64a < d64b)
    __builtin_abort ();
  d64a = d32c * d64b;
  if (d64a < d64b)
    __builtin_abort ();


  d32a = d32c + i;
  if (d32a != d32c + 2.0df)
    __builtin_abort ();
  d32a = d32c - i;
  if (d32a != d32c - 2.0df)
    __builtin_abort ();
  d32a = i * d32c;
  if (d32a != d32c + d32c)
    __builtin_abort ();
  d32a = d32c / i;
  if (d32a != d32c / 2.0df)
    __builtin_abort ();

  d64a = i + d64c;
  if (d64a != d64c + 2.0dd)
    __builtin_abort ();
  d64a = d64c - i;
  if (d64a != d64c - 2.0dd)
    __builtin_abort ();
  d64a = d64c * i;
  if (d64a != d64c + d64c)
    __builtin_abort ();
  d64a = d64c / i;
  if (d64a != d64c / 2.0dd)
    __builtin_abort ();

  d128a = d128c + i;
  if (d128a != d128c + 2.0dl)
    __builtin_abort ();
  d128a = d128c - i;
  if (d128a != d128c - 2.0dl)
    __builtin_abort ();
  d128a = i * d128c;
  if (d128a != d128c + d128c)
    __builtin_abort ();
  d128a = d128c / i;
  if (d128a != d128c / 2.0dl)
    __builtin_abort ();

  return 0;
}
