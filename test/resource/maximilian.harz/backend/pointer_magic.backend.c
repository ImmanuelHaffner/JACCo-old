2


int main()
{
  struct S { int x; } s;
  struct  *p;
  p = &s;
  p->x = 2;
  return (*p).x;
}
