1

int foo(char c)
{
	return 1;
}

int main()
{
  struct { int a; } x;
	foo(x);
}
