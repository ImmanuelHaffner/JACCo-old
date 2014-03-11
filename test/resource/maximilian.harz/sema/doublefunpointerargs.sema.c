0

int foo( int (*fp)(int), int nofp(int) );

int bar( int x );

int main()
{
  int (*p)(int);
  p = bar;
  foo( p, bar );
}
