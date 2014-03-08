0


int global;

int foo();

int main()
{
  global = 0;
  return global + foo();
}

int foo()
{
  global = 23;
  return 0;
}
