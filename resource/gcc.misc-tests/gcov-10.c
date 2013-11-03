




int main ()
{
  unsigned ix, jx = 0;

  for (ix = 10; ix--;) if (ix & 1) jx++;

  return jx != 5;
}
