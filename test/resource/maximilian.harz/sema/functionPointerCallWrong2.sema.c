int foo(char c)
{
	return 1;
}

int main()
{
	int c;
	int (*p)(char);
	p = &foo;
	(*p)(c);
}
