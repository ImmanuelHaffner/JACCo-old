int foo(char)
{
	return 1;
}

void main()
{
	char c;
	int x;
	int (*p)(char);
	p = &foo;
	x = p(c);
}
