80


int main()
{
  struct O
  {
    int x;
    int y;
  };
  struct O o;
  struct O *po;
  po = &o;
  o.x = 30;
  po->y = 50;
  return po->x + o.y;
}
