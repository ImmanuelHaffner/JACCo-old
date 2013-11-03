extern void abort (void);
double d = 1.17549435082228750797e-38F / 2.0;
int main()
{
  double x = 1.17549435082228750797e-38F / 2.0;
  if (x != d)
    abort ();
  return 0;
}
