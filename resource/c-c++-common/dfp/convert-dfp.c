int failures;

volatile _Decimal32 d32;
volatile _Decimal64 d64;
volatile _Decimal128 d128;

int
main ()
{

  d32 = 123.4df;
  d64 = d32;
  if (d64 != 123.4dd)
    __builtin_abort ();
  d128 = d32;
  if (d128 != 123.4dl)
    __builtin_abort ();
  d64 = 345.678dd;
  d128 = d64;
  if (d128 != 345.678dl)
    __builtin_abort ();


  d64 = 3456.789dd;
  d32 = d64;
  if (d32 != 3456.789df)
    __builtin_abort ();
  d128 = 123.4567dl;
  d32 = d128;
  if (d32 != 123.4567df)
    __builtin_abort ();

  d128 = 1234567890.123456dl;
  d64 = d128;
  if (d64 != 1234567890.123456dd)
    __builtin_abort ();
  d64 = 9.99999949E96DD;
  d32 = d64;
  if (d32 != 9.999999E96DF)
    __builtin_abort ();


  d64 = 9.9999995E96DD;
  d32 = d64;
  if (d32 != __builtin_infd32())
    __builtin_abort ();


  d128 = 9.99999949E96DD;
  d32 = d128;
  if (d32 != 9.999999E96DF)
    __builtin_abort ();


  d128= 9.9999995E96DD;
  d32 = d128;
  if (d32 != __builtin_infd32())
    __builtin_abort ();


  d128 = 9.99999999999999949E384DL;
  d64 = d128;
  if (d64 != 9.999999999999999E384DD)
    __builtin_abort ();


  d128 = 9.9999999999999995E384DL;
  d64 = d128;
  if (d64 != __builtin_infd64())
    __builtin_abort ();

  return 0;
}
