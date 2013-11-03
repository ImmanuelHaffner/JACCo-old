




int failures;

volatile _Decimal32 d32a, d32b, d32c;
volatile _Decimal64 d64a, d64b, d64c;
volatile _Decimal128 d128a, d128b, d128c;
volatile int i, yes, no;

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
  yes = 1;
  no = 0;
}

int
main ()
{
  init ();


  d32a = yes ? d32b : d32c;
  if (d32a != d32b)
    __builtin_abort ();
  d64a = no ? d64b : d64c;
  if (d64a != d64c)
    __builtin_abort ();
  d128a = yes ? d128b : d128c;
  if (d128a != d128b)
    __builtin_abort ();


  d128a = yes ? d32b : d64b;
  if (d128a != d32b)
    __builtin_abort ();
  d128a = yes ? d128b : d64b;
  if (d128a != d128b)
    __builtin_abort ();
  d128a = no ? d32b : d128b;
  if (d128a != d128b)
    __builtin_abort ();

  return 0;
}
