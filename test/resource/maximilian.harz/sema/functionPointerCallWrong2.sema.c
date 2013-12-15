int foo(char)
{
	return 1;
}

void main()
{
	int c;
	int (*p)(char);
	p = &foo;
	(*p)(c);
}
