1

int foo(char c)
{
	return 1;
}

int main()
{
	char c;
	struct { int a; } x;
	int (*p)(char);
	p = &foo;
	x = (*p)(c);
}
