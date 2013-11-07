

unsigned long long
foo (long long x)
{
  return -(unsigned long long) (x ? : x);
}
