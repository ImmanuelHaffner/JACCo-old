2


int main()
{
  struct S { int x; } * s;
  struct S ps;
  s = &ps;
  s->x = 2;
  return s->x;
}
