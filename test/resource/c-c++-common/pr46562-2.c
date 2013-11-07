


static const int a[4] = {};
int foo(void)
{
  int i = 1;
  const int *p = &a[i];
  return *p;
}
