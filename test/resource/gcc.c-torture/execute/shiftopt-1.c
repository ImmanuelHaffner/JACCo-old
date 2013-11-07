





extern void abort (void);
extern void link_error (void);

void
utest (unsigned int x)
{
  if (x >> 0 != x)
    link_error ();

  if (x << 0 != x)
    link_error ();

  if (0 << x != 0)
    link_error ();

  if (0 >> x != 0)
    link_error ();

  if (-1 >> x != -1)
    link_error ();

  if (~0 >> x != ~0)
    link_error ();
}

void
stest (int x)
{
  if (x >> 0 != x)
    link_error ();

  if (x << 0 != x)
    link_error ();

  if (0 << x != 0)
    link_error ();

  if (0 >> x != 0)
    link_error ();
}

int
main ()
{
  utest(9);
  utest(0);

  stest(9);
  stest(0);

  return 0;
}


void
link_error ()
{
  abort ();
}
