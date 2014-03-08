2


int main()
{
  struct S { int x; } * s;
  s->x = 2;
  return (*s).x;
}
