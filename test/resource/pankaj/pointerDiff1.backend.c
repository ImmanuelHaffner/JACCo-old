10


int main()
{
  int x;
  int y;
  x = 25;
  y = 30;
  int *p;
  p = &x;
  int *q;
  q = &y;
  if(p - q)
  {
    return 10;
  }
  return 11;
}
