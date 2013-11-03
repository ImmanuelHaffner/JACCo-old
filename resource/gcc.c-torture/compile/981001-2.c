






int
__add3(int d, int m, int c)
{
  return d + m + c;
}

extern __typeof (__add3) add3 __attribute__ ((weak, alias ("__add3")));
