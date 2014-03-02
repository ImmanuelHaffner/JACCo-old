0

int f(int x)
{
  x = 2;
  return x;
}
int main()
{
  int (*pf)(int);
  pf = f;
  int result;
  result = pf(20);
  result = f(20);
  pf = &f;
  result = pf(20);
  return 0;
}
