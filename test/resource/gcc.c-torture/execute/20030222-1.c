






















void
ll_to_int (long long x, volatile int *p)
{
  int i;
  asm ("" : "=r" (i) : "0" (x));
  *p = i;
}

int val = (-2147483647 - 1) + 1;

int main() {
  volatile int i;

  ll_to_int ((long long)val, &i);
  if (i != val)
    abort ();

  exit (0);
}
