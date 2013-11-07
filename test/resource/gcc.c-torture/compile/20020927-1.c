



int
foo ()
{
  int i;
  long long int j;

  while (1)
    {
      if (j & 1)
 ++i;
      j >>= 1;
      if (j)
 return i;
    }
}

int
bar ()
{
  if (foo ())
    return;
}
