int count;

void incr_count ()
{
  count++;
}

void doit (int i, int j)
{
  if (i > j)
    incr_count ();
}

int main ()
{
  int i, j;

  for (i = 0; i < 7000; i++)
    for (j = 0; j < 7000; j++)
      doit (i, j);

  return 0;
}
