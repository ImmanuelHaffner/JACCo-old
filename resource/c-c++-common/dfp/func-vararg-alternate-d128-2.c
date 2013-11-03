


int failures;
typedef __builtin_va_list __gnuc_va_list;
typedef __gnuc_va_list va_list;

_Decimal128 a[10];
double b[10];

union U {
  _Decimal128 d;
  unsigned int i[4];
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
    a[j] = __builtin_va_arg(ap,_Decimal128);
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
      a[j] = __builtin_va_arg(ap,_Decimal128);
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
      a[j] = __builtin_va_arg(ap,_Decimal128);
    }
  __builtin_va_end(ap);
}

void
doit ()
{
  _Decimal128 x, y, z;
  union U u1, u2;



  if (4 * 4 != sizeof (_Decimal128))
    {




      __builtin_abort ();
    }

  x = 1.0dl / 3.0dl;
  y = 1.0dl / 7.0dl;
  z = 1.0dl / 11.0dl;

  bar0 (1, x);
  u1.d = x; u2.d = a[0]; compare (0.0, 0.0, u1.i, u2.i, 4, 109);

  bar0 (2, x, y);
  u1.d = x; u2.d = a[0]; compare (0.0, 0.0, u1.i, u2.i, 4, 112);
  u1.d = y; u2.d = a[1]; compare (0.0, 0.0, u1.i, u2.i, 4, 113);

  bar0 (3, x, y, z);
  u1.d = x; u2.d = a[0]; compare (0.0, 0.0, u1.i, u2.i, 4, 116);
  u1.d = y; u2.d = a[1]; compare (0.0, 0.0, u1.i, u2.i, 4, 117);
  u1.d = z; u2.d = a[2]; compare (0.0, 0.0, u1.i, u2.i, 4, 118);

  bar1 (1, x, 1.5);
  u1.d = x; u2.d = a[0]; compare (1.5, b[0], u1.i, u2.i, 4, 121);

  bar1 (2, x, 1.5, y, 2.5);
  u1.d = x; u2.d = a[0]; compare (1.5, b[0], u1.i, u2.i, 4, 124);
  u1.d = y; u2.d = a[1]; compare (2.5, b[1], u1.i, u2.i, 4, 125);

  bar1 (3, x, 1.5, y, 2.5, z, 3.5);
  u1.d = x; u2.d = a[0]; compare (1.5, b[0], u1.i, u2.i, 4, 128);
  u1.d = y; u2.d = a[1]; compare (2.5, b[1], u1.i, u2.i, 4, 129);
  u1.d = z; u2.d = a[2]; compare (3.5, b[2], u1.i, u2.i, 4, 130);

  bar2 (1, 1.5, x);
  u1.d = x; u2.d = a[0]; compare (1.5, b[0], u1.i, u2.i, 4, 133);

  bar2 (2, 1.5, x, 2.5, y);
  u1.d = x; u2.d = a[0]; compare (1.5, b[0], u1.i, u2.i, 4, 136);
  u1.d = y; u2.d = a[1]; compare (2.5, b[1], u1.i, u2.i, 4, 137);

  bar2 (3, 1.5, x, 2.5, y, 3.5, z);
  u1.d = x; u2.d = a[0]; compare (1.5, b[0], u1.i, u2.i, 4, 140);
  u1.d = y; u2.d = a[1]; compare (2.5, b[1], u1.i, u2.i, 4, 141);
  u1.d = z; u2.d = a[2]; compare (3.5, b[2], u1.i, u2.i, 4, 142);
}

int
main ()
{
  doit ();

  return 0;
}
