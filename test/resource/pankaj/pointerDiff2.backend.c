11


int main()
{
  int x;
  int y;
  x = 25;
  y = 30;
  int *p;
  p = &x;
  if(p - &x)
  {
    return 10;
  }
  return 11;
}
