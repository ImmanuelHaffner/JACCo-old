


int main (void)
{
  extern int foo ();
  return _Cilk_spawn foo ();
}
