


double func (const double *array)
{
  double d = *array;
  if (d == 1.0)
    return d;
  else
    return d * func (array + 1);
}

int main ()
{
  double values[] = { ((double)1.79769313486231570815e+308L), 2.0, 0.5, 1.0 };
  if (func (values) != ((double)1.79769313486231570815e+308L))
    abort ();
  exit (0);
}
