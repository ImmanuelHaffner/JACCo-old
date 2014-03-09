8


int main()
{
  struct O
  {
    int x;
    int y;
  };
  struct O o;
  o.x = 3;
  o.y = 5;
  return o.x + o.y;
}
