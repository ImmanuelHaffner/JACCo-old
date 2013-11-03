


int failures;

volatile float f = __builtin_inff ();
volatile _Decimal32 d32 = 1e40DF;

int
main (void)
{
  if ((double) f == (double) d32)
    __builtin_abort ();

  return 0;
}
