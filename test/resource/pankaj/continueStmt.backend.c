3


int main()
{
  int x;
  int y;
  x = 0;
  while(x < 5)
  {
    x = x + 1;
    if(x == 4)
    {
      x = x + 1;
      continue;
    }
    y = x;

  }
  return y;
}
