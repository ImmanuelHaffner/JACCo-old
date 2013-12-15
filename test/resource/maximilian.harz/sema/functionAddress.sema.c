int foo(char c)
{
	return 1;
}

void main()
{
	int (*p)(char x);
	(p = &foo);
}
