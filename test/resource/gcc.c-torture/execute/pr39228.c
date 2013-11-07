extern void abort (void);

static int __attribute__((always_inline)) testf (float b)
{
  float c = 1.01f * b;

  return __builtin_isinff (c);
}

static int __attribute__((always_inline)) test (double b)
{
  double c = 1.01 * b;

  return __builtin_isinf (c);
}

static int __attribute__((always_inline)) testl (long double b)
{
  long double c = 1.01L * b;

  return __builtin_isinfl (c);
}

int main()
{
  if (testf (3.40282346638528859812e+38F) < 1)
    abort ();

  if (test (((double)1.79769313486231570815e+308L)) < 1)
    abort ();

  if (testl (1.18973149535723176502e+4932L) < 1)
    abort ();

  return 0;
}
