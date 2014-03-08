23

int global;

int foo();

int main()
{
  return foo() + global;
}

int foo()
{
  global = 23;
  return 0;
}
