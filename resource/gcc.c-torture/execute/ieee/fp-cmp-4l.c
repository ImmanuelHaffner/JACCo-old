




void
test_isunordered(long double x, long double y, int true)
{
  if (__builtin_isunordered(x, y))
    {
      if (! true)
 abort ();
    }
  else
    {
      if (true)
 abort ();
    }
}

void
test_isless(long double x, long double y, int true)
{
  if (__builtin_isless(x, y))
    {
      if (! true)
 abort ();
    }
  else
    {
      if (true)
 abort ();
    }
}

void
test_islessequal(long double x, long double y, int true)
{
  if (__builtin_islessequal(x, y))
    {
      if (! true)
 abort ();
    }
  else
    {
      if (true)
 abort ();
    }
}

void
test_isgreater(long double x, long double y, int true)
{
  if (__builtin_isgreater(x, y))
    {
      if (! true)
 abort ();
    }
  else
    {
      if (true)
 abort ();
    }
}

void
test_isgreaterequal(long double x, long double y, int true)
{
  if (__builtin_isgreaterequal(x, y))
    {
      if (! true)
 abort ();
    }
  else
    {
      if (true)
 abort ();
    }
}

void
test_islessgreater(long double x, long double y, int true)
{
  if (__builtin_islessgreater(x, y))
    {
      if (! true)
 abort ();
    }
  else
    {
      if (true)
 abort ();
    }
}



int
main()
{
  struct try
  {
    long double x, y;
    unsigned unord : 1;
    unsigned lt : 1;
    unsigned le : 1;
    unsigned gt : 1;
    unsigned ge : 1;
    unsigned lg : 1;
  };

  static struct try const data[] =
  {
    { (0.0 / 0.0), (0.0 / 0.0), 1, 0, 0, 0, 0, 0 },
    { 0.0, (0.0 / 0.0), 1, 0, 0, 0, 0, 0 },
    { (0.0 / 0.0), 0.0, 1, 0, 0, 0, 0, 0 },
    { 0.0, 0.0, 0, 0, 1, 0, 1, 0 },
    { 1.0, 2.0, 0, 1, 1, 0, 0, 1 },
    { 2.0, 1.0, 0, 0, 0, 1, 1, 1 },
  };

  const int n = sizeof(data) / sizeof(data[0]);
  int i;

  for (i = 0; i < n; ++i)
    {
      test_isunordered (data[i].x, data[i].y, data[i].unord);
      test_isless (data[i].x, data[i].y, data[i].lt);
      test_islessequal (data[i].x, data[i].y, data[i].le);
      test_isgreater (data[i].x, data[i].y, data[i].gt);
      test_isgreaterequal (data[i].x, data[i].y, data[i].ge);
      test_islessgreater (data[i].x, data[i].y, data[i].lg);
    }

  exit (0);
}
