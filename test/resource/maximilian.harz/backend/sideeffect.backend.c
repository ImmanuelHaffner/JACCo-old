23


int global;

int foo();

int main()
{
  global = 0;
  return foo() + global;
}

int foo()
{
  global = 23;
  return 0;
}
