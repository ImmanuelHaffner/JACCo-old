




extern void __cilkrts_set_param (char *, char *);

void foo(volatile int *);

void main2(void);

int main(void)
{

  main2();
  return 0;
}


void main2(void)
{
  int some_var = 0;

  _Cilk_spawn foo(&some_var);

  some_var=1;
  some_var=5;
  some_var=3;
  some_var=4;

  _Cilk_sync;
  return;
}

void foo(volatile int *some_other_var)
{
  while (*some_other_var == 0)
  {
   ;
  }
}
