


int failures;
typedef __builtin_va_list __gnuc_va_list;
typedef __gnuc_va_list va_list;

DTYPE a[10];
double b[10];

union U {
  DTYPE d;
  unsigned int i[INTS];
};

void
compare (double r, double s, unsigned int *p, unsigned int *q, int n, int line)
{
  int i;

  for (i = 0; i < n; i++)
    if (r != s || p[i] != q[i])
      __builtin_abort ();

}

void
bar0 (int n, ...)
{
  union U u;
  int j;
  va_list ap;

  __builtin_va_start(ap,n);
  for (j = 0; j < n; j++)
    a[j] = __builtin_va_arg(ap,DTYPE);
  __builtin_va_end(ap);
}

void
bar1 (int n, ...)
{
  union U u;
  int j;
  va_list ap;

  __builtin_va_start(ap,n);
  for (j = 0; j < n; j++)
    {
      a[j] = __builtin_va_arg(ap,DTYPE);
      b[j] = __builtin_va_arg(ap,double);
    }
  __builtin_va_end(ap);
}

void
bar2 (int n, ...)
{
  union U u;
  int j;
  va_list ap;

  __builtin_va_start(ap,n);
  for (j = 0; j < n; j++)
    {
      b[j] = __builtin_va_arg(ap,double);
      a[j] = __builtin_va_arg(ap,DTYPE);
    }
  __builtin_va_end(ap);
}

void
doit ()
{
  DTYPE x, y, z;
  union U u1, u2;



  if (INTS * 4 != sizeof (DTYPE))
    {




      __builtin_abort ();
    }

  x = ONE / THREE;
  y = ONE / SEVEN;
  z = ONE / ELEVEN;

  bar0 (1, x);
  u1.d = x; u2.d = a[0]; compare (0.0, 0.0, u1.i, u2.i, INTS, 109);

  bar0 (2, x, y);
  u1.d = x; u2.d = a[0]; compare (0.0, 0.0, u1.i, u2.i, INTS, 112);
  u1.d = y; u2.d = a[1]; compare (0.0, 0.0, u1.i, u2.i, INTS, 113);

  bar0 (3, x, y, z);
  u1.d = x; u2.d = a[0]; compare (0.0, 0.0, u1.i, u2.i, INTS, 116);
  u1.d = y; u2.d = a[1]; compare (0.0, 0.0, u1.i, u2.i, INTS, 117);
  u1.d = z; u2.d = a[2]; compare (0.0, 0.0, u1.i, u2.i, INTS, 118);

  bar1 (1, x, 1.5);
  u1.d = x; u2.d = a[0]; compare (1.5, b[0], u1.i, u2.i, INTS, 121);

  bar1 (2, x, 1.5, y, 2.5);
  u1.d = x; u2.d = a[0]; compare (1.5, b[0], u1.i, u2.i, INTS, 124);
  u1.d = y; u2.d = a[1]; compare (2.5, b[1], u1.i, u2.i, INTS, 125);

  bar1 (3, x, 1.5, y, 2.5, z, 3.5);
  u1.d = x; u2.d = a[0]; compare (1.5, b[0], u1.i, u2.i, INTS, 128);
  u1.d = y; u2.d = a[1]; compare (2.5, b[1], u1.i, u2.i, INTS, 129);
  u1.d = z; u2.d = a[2]; compare (3.5, b[2], u1.i, u2.i, INTS, 130);

  bar2 (1, 1.5, x);
  u1.d = x; u2.d = a[0]; compare (1.5, b[0], u1.i, u2.i, INTS, 133);

  bar2 (2, 1.5, x, 2.5, y);
  u1.d = x; u2.d = a[0]; compare (1.5, b[0], u1.i, u2.i, INTS, 136);
  u1.d = y; u2.d = a[1]; compare (2.5, b[1], u1.i, u2.i, INTS, 137);

  bar2 (3, 1.5, x, 2.5, y, 3.5, z);
  u1.d = x; u2.d = a[0]; compare (1.5, b[0], u1.i, u2.i, INTS, 140);
  u1.d = y; u2.d = a[1]; compare (2.5, b[1], u1.i, u2.i, INTS, 141);
  u1.d = z; u2.d = a[2]; compare (3.5, b[2], u1.i, u2.i, INTS, 142);
}
