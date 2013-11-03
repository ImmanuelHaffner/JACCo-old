









extern void __assert_fail (__const char *__assertion, __const char *__file,
      unsigned int __line, __const char *__function)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));


extern void __assert_perror_fail (int __errnum, __const char *__file,
      unsigned int __line,
      __const char *__function)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));




extern void __assert (const char *__assertion, const char *__file, int __line)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));




int a, *b, c, d, f, **i, p, q, *r;
short o, j;

static int __attribute__((noinline, noclone))
fn1 (int *p1, int **p2)
{
  int **e = &b;
  for (; p; p++)
    *p1 = 1;
  *e = *p2 = &d;

  ((r) ? (void) (0) : __assert_fail ("r", "raw/gcc.c-torture/execute/pr58831.c", 14, __PRETTY_FUNCTION__));

  return c;
}

static int ** __attribute__((noinline, noclone))
fn2 (void)
{
  for (f = 0; f != 42; f++)
    {
      int *g[3] = {0, 0, 0};
      for (o = 0; o; o--)
        for (; a > 1;)
          {
            int **h[1] = { &g[2] };
          }
    }
  return &r;
}

int
main (void)
{
  i = fn2 ();
  fn1 (b, i);
  return 0;
}
