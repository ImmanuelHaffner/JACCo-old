




extern inline int t()
{
  int q() { return 0; }

  return q();
}

int foo()
{
  return t();
}
