

extern void f2 (int);

void bar (int x, int y, int z)
{



  f2 (x < y ? : 1);
  f2 (x > y ? : 1);
  f2 (x <= y ? : 1);
  f2 (x >= y ? : 1);
  f2 (x == y ? : 1);
  f2 (x != y ? : 1);
  f2 (x || y ? : 1);
  f2 (x && y ? : 1);
  f2 (!x ? : 1);
  f2 (x < y ? 2 : 1);
  f2 (x > y ? 2 : 1);
  f2 (x == y ? 2 : 1);
  f2 (x || y ? 2 : 1);
  f2 (x && y ? 2 : 1);
  f2 (x + y ? : 1);
  f2 (x - y ? : 1);
  f2 (x * y ? : 1);
  f2 (x / y ? : 1);
  f2 (x ^ y ? : 1);
}
