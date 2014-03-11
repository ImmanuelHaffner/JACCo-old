0

struct S
{
  char d;
  struct T
  {
    char b;
    int (*g)(int);
    int c;
  } *pt;
  int (*f)(int);
  struct T t;
  int a;
};

int f(int x)
{
  return 20;
}

int g(int y)
{
  return 30;
}
int main()
{
  struct S s;
  s.a = 10;
  int (*h)(int);
  h(0);
  s.f = &f;
  s.pt = &s.t;

  return s.a + (s.f)(0) + (s.pt->g)(1);
}
