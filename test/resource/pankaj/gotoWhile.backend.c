2


int main()
{
  int x;
  x = 1;
  int y;
  while(x < 5)
  {
    y = 1;
    x = x + 1;
label:
    if(x == 5)
    y = 2;
  }
  if(y == 1)
  goto label;
  return y;
}
