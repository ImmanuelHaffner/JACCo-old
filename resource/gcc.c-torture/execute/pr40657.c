


long long v = 0x123456789abc;

__attribute__((noinline)) void bar (int *x)
{
  asm volatile ("" : "=m" (x) ::);
}

__attribute__((noinline)) long long foo()
{
  int x;
  bar(&x);
  return v;
}

int main ()
{
  if (foo () != v)
    abort ();
  exit (0);
}
