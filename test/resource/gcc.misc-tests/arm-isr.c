extern void abort ();
extern void exit (int);
int z = 9;

int
bar (void)
{
  return z;
}

int
foo (int a, int b, int c, int d, int e, int f, int g, int h)
{
  volatile int i = (a + b) - (g + h) + bar ();
  volatile int j = (e + f) - (c + d);

  return a + b + c + d + e + f + g + h + i + j;
}

int foo1 (int a, int b, int c, int d, int e, int f, int g, int h) __attribute__ ((interrupt ("IRQ")));

int
foo1 (int a, int b, int c, int d, int e, int f, int g, int h)
{
  volatile int i = (a + b) - (g + h) + bar ();
  volatile int j = (e + f) - (c + d);

  return a + b + c + d + e + f + g + h + i + j;
}


int
main (void)
{

  if (foo (1, 2, 3, 4, 5, 6, 7, 8) != 32)
    abort ();

  if (foo1 (1, 2, 3, 4, 5, 6, 7, 8) != 32)
    abort ();

  exit (0);
}
