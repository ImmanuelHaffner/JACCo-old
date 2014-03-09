100


int main()
{
  struct O
  {
    int x;
    int y;
    struct P
    {
      int v;
      int w;
    } p;
    struct P *pp;
  };
  struct O o;
  o.x = 10;
  o.y = 20;
  o.pp = &o.p;
  o.p.v = 30;
  o.pp->w = 40;
  return o.x + o.y + o.pp->v + o.p.w;
}
