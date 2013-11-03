





int failures;



void
runtime32 (void)
{
  volatile _Decimal32 d;
  d = 0.0DF;
  if (d)
    __builtin_abort ();
}

void
runtime64 (void)
{
  volatile _Decimal64 d;
  d = 0.0DD;
  if (d)
    __builtin_abort ();
}

void
runtime128 (void)
{
  volatile _Decimal128 d;
  d = 0.0DL;
  if (d)
    __builtin_abort ();
}

void
fold32 (void)
{
  if (0.0DF)
    __builtin_abort ();
}

void
fold64 (void)
{
  if (0.0DD)
    __builtin_abort ();
}

void
fold128 (void)
{
  if (0.0DL)
    __builtin_abort ();
}

int
main(void)
{
  runtime32 ();
  runtime64 ();
  runtime128 ();

  fold32 ();
  fold64 ();
  fold128 ();

  return 0;
}
