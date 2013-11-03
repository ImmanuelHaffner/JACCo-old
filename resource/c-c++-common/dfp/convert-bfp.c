





int failures;

static int skip_long_double;

volatile _Decimal32 d32;
volatile _Decimal64 d64;
volatile _Decimal128 d128;
volatile float sf;
volatile double df;
volatile long double tf;

int
main ()
{


  if (sizeof (long double) == sizeof (double))
    skip_long_double = 1;


  d32 = 2.0df;
  sf = d32;
  if (sf != 2.0f)
    __builtin_abort ();

  df = d32;
  if (df != 2.0)
    __builtin_abort ();

  if (skip_long_double == 0)
    {
      tf = d32;
      if (tf != 2.0l)
 __builtin_abort ();
    }


  d64 = -7.0dd;
  sf = d64;
  if (sf != -7.0f)
    __builtin_abort ();

  df = d64;
  if (df != -7.0)
    __builtin_abort ();

  if (skip_long_double == 0)
    {
      tf = d64;
      if (tf != -7.0l)
 __builtin_abort ();
    }


  d128 = 30.0dl;
  sf = d128;
  if (sf != 30.0f)
    __builtin_abort ();

  df = d128;
  if (df != 30.0)
    __builtin_abort ();

  df = d128;
  if (df != 30.0l)
    __builtin_abort ();


  sf = 30.0f;
  d32 = sf;
  if (d32 != 30.0df)
    __builtin_abort ();

  d64 = sf;
  if (d64 != 30.0dd)
    __builtin_abort ();

  df = -2.0;
  d32 = df;
  if (d32 != -2.0df)
    __builtin_abort ();

  d64 = df;
  if (d64 != -2.0dd)
    __builtin_abort ();

  d128 = df;
  if (d128 != -2.0dl)
    __builtin_abort ();

  sf = 30.0f;
  d128 = sf;
  if (d128 != 30.0dl)
    __builtin_abort ();

  if (skip_long_double == 0)
    {
      tf = -22.0l;
      d32 = tf;
      if (d32 != -22.0df)
 __builtin_abort ();

      d64 = tf;
      if (d64 != -22.0dd)
 __builtin_abort ();

      d128 = tf;
      if (d128 != -22.0dl)
 __builtin_abort ();
     }


  d128 = 0.000488281251dl;
  sf = d128;
  if (sf != 0.00048828125f)
    __builtin_abort ();

  d128 = 2.98023223876953125E-8dl;
  df = d128;
  if (df < (2.9802322387695312e-08 - 0.00000000001)
      || df > (2.9802322387695312e-08 + 0.00000000001))
    __builtin_abort ();

  return 0;
}
