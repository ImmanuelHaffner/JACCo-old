






static float
test_isunordered(float x, float y, float a, float b)
{
  return __builtin_isunordered(x, y) ? a : b;
}

static float
test_not_isunordered(float x, float y, float a, float b)
{
  return !__builtin_isunordered(x, y) ? a : b;
}

static float
test_isless(float x, float y, float a, float b)
{
  return __builtin_isless(x, y) ? a : b;
}

static float
test_not_isless(float x, float y, float a, float b)
{
  return !__builtin_isless(x, y) ? a : b;
}

static float
test_islessequal(float x, float y, float a, float b)
{
  return __builtin_islessequal(x, y) ? a : b;
}

static float
test_not_islessequal(float x, float y, float a, float b)
{
  return !__builtin_islessequal(x, y) ? a : b;
}

static float
test_isgreater(float x, float y, float a, float b)
{
  return __builtin_isgreater(x, y) ? a : b;
}

static float
test_not_isgreater(float x, float y, float a, float b)
{
  return !__builtin_isgreater(x, y) ? a : b;
}

static float
test_isgreaterequal(float x, float y, float a, float b)
{
  return __builtin_isgreaterequal(x, y) ? a : b;
}

static float
test_not_isgreaterequal(float x, float y, float a, float b)
{
  return !__builtin_isgreaterequal(x, y) ? a : b;
}

static float
test_islessgreater(float x, float y, float a, float b)
{
  return __builtin_islessgreater(x, y) ? a : b;
}

static float
test_not_islessgreater(float x, float y, float a, float b)
{
  return !__builtin_islessgreater(x, y) ? a : b;
}

static void
one_test(float x, float y, int expected,
         float (*pos) (float, float, float, float),
  float (*neg) (float, float, float, float))
{
  if (((*pos)(x, y, 1.0, 2.0) == 1.0) != expected)
    abort ();
  if (((*neg)(x, y, 3.0, 4.0) == 4.0) != expected)
    abort ();
}




int
main()
{
  struct try
  {
    float x, y;
    int result[6];
  };

  static struct try const data[] =
  {
    { (0.0 / 0.0), (0.0 / 0.0), { 1, 0, 0, 0, 0, 0 } },
    { 0.0, (0.0 / 0.0), { 1, 0, 0, 0, 0, 0 } },
    { (0.0 / 0.0), 0.0, { 1, 0, 0, 0, 0, 0 } },
    { 0.0, 0.0, { 0, 0, 1, 0, 1, 0 } },
    { 1.0, 2.0, { 0, 1, 1, 0, 0, 1 } },
    { 2.0, 1.0, { 0, 0, 0, 1, 1, 1 } },
    { (1.0 / 0.0), 0.0, { 0, 0, 0, 1, 1, 1 } },
    { 1.0, (1.0 / 0.0), { 0, 1, 1, 0, 0, 1 } },
    { (1.0 / 0.0), (1.0 / 0.0), { 0, 0, 1, 0, 1, 0 } },
    { 0.0, -(1.0 / 0.0), { 0, 0, 0, 1, 1, 1 } },
    { -(1.0 / 0.0), 1.0, { 0, 1, 1, 0, 0, 1 } },
    { -(1.0 / 0.0), -(1.0 / 0.0), { 0, 0, 1, 0, 1, 0 } },
    { (1.0 / 0.0), -(1.0 / 0.0), { 0, 0, 0, 1, 1, 1 } },
    { -(1.0 / 0.0), (1.0 / 0.0), { 0, 1, 1, 0, 0, 1 } },
  };

  struct test
  {
    float (*pos)(float, float, float, float);
    float (*neg)(float, float, float, float);
  };

  static struct test const tests[] =
  {
    { test_isunordered, test_not_isunordered },
    { test_isless, test_not_isless },
    { test_islessequal, test_not_islessequal },
    { test_isgreater, test_not_isgreater },
    { test_isgreaterequal, test_not_isgreaterequal },
    { test_islessgreater, test_not_islessgreater }
  };

  const int n = sizeof(data) / sizeof(data[0]);
  int i, j;

  for (i = 0; i < n; ++i)
    for (j = 0; j < 6; ++j)
      one_test (data[i].x, data[i].y, data[i].result[j],
  tests[j].pos, tests[j].neg);

  exit (0);
}
