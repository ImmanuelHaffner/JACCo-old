

inline double bar(double x)
{
  long double d;
  __asm__ ("" : "=t" (d) : "0" (x));
  return d;
}

double foo(double x)
{
  if (x)
    return bar(x);
  else
    return bar(x);
}
