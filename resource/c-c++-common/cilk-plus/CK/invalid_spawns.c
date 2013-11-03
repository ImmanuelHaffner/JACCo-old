extern int foo ();
int bar = _Cilk_spawn foo ();


int main (void)
{
  int x;

  _Cilk_spawn x;
  return x;
}
