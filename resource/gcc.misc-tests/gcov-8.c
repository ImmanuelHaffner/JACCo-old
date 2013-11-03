int proxy (int i)
{
  return i;
}

int foo (int i)
{
  if (i > 0)
    return proxy (1);
  else if (i < 0)
    return proxy (-1);
  else
    return proxy (0);
}

int baz (int i)
{
  if (i == 0)
    return proxy (0);
  else if (i > 0)
    return proxy (1);
  else
    return proxy (-1);
}

int main ()
{
  int t = 0;
  int ix;

  for (ix = 0; ix != 1000; ix++)
    t += foo (ix) + baz (ix);

  return t == 0;
}
