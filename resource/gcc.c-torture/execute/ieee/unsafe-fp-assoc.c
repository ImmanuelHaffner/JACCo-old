
extern void abort(void);

static const double C = ((double)1.79769313486231570815e+308L);

double foo(double x)
{
        return ( ( (x * C) * C ) * C);
}

int main ()
{
  double d = foo (0.0);
  if (d != 0.0)
   abort ();

  return 0;
}
