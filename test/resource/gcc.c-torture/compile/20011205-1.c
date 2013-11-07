



long foo()
{
  long x;
  asm("" : "=r"(x) : "m"(x));
  return x;
}
