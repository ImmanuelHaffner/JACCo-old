


int failures;

volatile _Decimal32 f = 1.23456DF;
volatile _Decimal64 d = 1.23456DD;

int
main (void)
{
  if ((_Decimal128)((_Decimal64)f * (_Decimal64)f) != (_Decimal128)(d * d))
    __builtin_abort ();
  return 0;
}
