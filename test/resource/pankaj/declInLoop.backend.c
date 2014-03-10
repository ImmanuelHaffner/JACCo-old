10


int main()
{
  int i;
  i = 5;
  if(i == 4)
  {
    return 1;
  }
  while (i < 10)
  {
    int x;
    x = i;
    i = x + 1;
  }
  return i;
}
