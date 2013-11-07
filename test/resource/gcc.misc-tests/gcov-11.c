




int one = 1;
int zero = 0;

int foo (int ix)
{
  return ix & 1 ? one : zero;
}

int main ()
{
  unsigned ix, jx = 0;

  for (ix = 10; ix--;) jx += foo (ix);

  return jx != 5;
}
