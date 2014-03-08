3


int main()
{
  int x;
  x = 21;
  if(x == 21)
  {
    x = 2;
  }
  else
  {
label:
    x = 3;
  }
  if(x == 2)
  goto label;
  return x;
}
