extern int __attribute__ ((weak)) Foo ();

extern __inline int Foo ()
{
  return 0;
}

int (* __attribute__ ((noinline)) Bar ()) ()
{
  return Foo;
}

int main ()
{
  return Bar () != 0;
}
