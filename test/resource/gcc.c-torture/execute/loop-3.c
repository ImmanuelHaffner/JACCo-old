
















int n = 0;

g (i)
{
  n++;
}

f (m)
{
  int i;
  i = m;
  do
    {
      g (i * 2147483647 / 2);
    }
  while (--i > 0);
}

main ()
{
  f (4);
  if (n != 4)
    abort ();
  exit (0);
}
