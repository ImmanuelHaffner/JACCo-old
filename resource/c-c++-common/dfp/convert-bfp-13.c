


int failures;

volatile double d = 1.2345675;

typedef const volatile _Decimal32 d32;

int
main (void)
{
  _Decimal32 a = (d * d);
  d32 b = (d * d);
  if (a != b)
    __builtin_abort ();
  return 0;
}
