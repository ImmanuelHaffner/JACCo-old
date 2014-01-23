1

int foo(char c)
{
	return 1;
}

int main()
{
  struct { int a; } c;	
	int (*p)(char);
	p = &foo;
	(*p)(c);
}
