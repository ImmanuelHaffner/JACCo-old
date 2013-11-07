

int
foo (void)
{
  int x = 0;
  goto *&x;
}
