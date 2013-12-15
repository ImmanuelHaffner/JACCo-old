int foo(char)
{
	return 1;
}

void main()
{
	char c;
	char x;
	int (*p)(char);
	p = &foo;
	x = (*p)(c);
}
