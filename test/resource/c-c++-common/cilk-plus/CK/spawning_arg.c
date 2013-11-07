



void f0(volatile int *steal_flag)
{
  int i = 0;

  while (!*steal_flag)
    ;
}

int f1()
{

  volatile int steal_flag = 0;
  _Cilk_spawn f0(&steal_flag);
  steal_flag = 1;
  _Cilk_sync;
  return 0;
}

void f2(int q)
{
  q = 5;
}

void f3()
{
   _Cilk_spawn f2(f1());
}

int main()
{
  f3();
  return 0;
}
