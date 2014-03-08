31


int f(int a, int b)
{
  return a + b;
}
int main()
{
  int (*pf)(int, int);
  pf = &f;
  return pf(11, 20);
}
