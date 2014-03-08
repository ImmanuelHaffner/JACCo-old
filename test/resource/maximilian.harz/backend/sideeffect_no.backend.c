0

int global;

int foo();

int main()
{
  return global + foo();
}

int foo()
{
  global = 23;
  return 0;
}
