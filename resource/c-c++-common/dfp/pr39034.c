





int failures;



void
runtime32 (void)
{
  volatile float v1 = 28.f, v2 = 3.f, v3 = 9.f, v4 = 31.f, v5 = 3.f, v6 = 10.f;
  float b32 = (float)((v1/v2-v3) - (v4/v5-v6));
  _Decimal32 d32 = (float)((v1/v2-v3) - (v4/v5-v6));

  if (b32)
    __builtin_abort ();
  if (d32)
    __builtin_abort ();
}

void
runtime64 (void)
{
  volatile double v1 = 28., v2 = 3., v3 = 9., v4 = 31., v5 = 3., v6 = 10.;
  double b64 = (double)((v1/v2-v3) - (v4/v5-v6));
  _Decimal64 d64 = (double)((v1/v2-v3) - (v4/v5-v6));

  if (b64)
    __builtin_abort ();
  if (d64)
    __builtin_abort ();
}

void
runtime128 (void)
{
  volatile long double v1 = 28.l, v2 = 3.l, v3 = 9.l,
                       v4 = 31.l, v5 = 3.l, v6 = 10.l;
  long double b128 = (long double)((v1/v2-v3) - (v4/v5-v6));
  _Decimal128 d128 = (long double)((v1/v2-v3) - (v4/v5-v6));

  if (b128)
    __builtin_abort ();
  if (d128)
    __builtin_abort ();
}



void
fold32 (void)
{
  double d32 = (float)((28.f/3.f-9.f) - (31.f/3.f-10.f));
  _Decimal32 b32 = (float)((28.f/3.f-9.f) - (31.f/3.f-10.f));

  if (b32)
    __builtin_abort ();
  if (d32)
    __builtin_abort ();
}

void
fold64 (void)
{
  double b64 = (double)((28./3.-9.) - (31./3.-10.));
  _Decimal64 d64 = (double)((28./3.-9.) - (31./3.-10.));

  if (b64)
    __builtin_abort ();
  if (d64)
    __builtin_abort ();
}

void
fold128 (void)
{
  long double b128 = (long double)((28./3.-9.) - (31./3.-10.));
  _Decimal128 d128 = (long double)((28./3.-9.) - (31./3.-10.));

  if (b128)
    __builtin_abort ();
  if (d128)
    __builtin_abort ();
}

int
main ()
{
  runtime32 ();
  runtime64 ();
  runtime128 ();
  fold32 ();
  fold64 ();
  fold128 ();

  return 0;
}
