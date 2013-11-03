




int main ()
{
  unsigned ix, jx = 0;

  ix = 10; goto test; loop: ; if (ix & 1) jx++; test: ; if (ix--) goto loop;

  return jx != 5;
}
