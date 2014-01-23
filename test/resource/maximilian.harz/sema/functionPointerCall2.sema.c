0

int foo(char c)
{
	return 1;
}

int main()
{
	char c;
	int x;
	int (*p)(char);
	p = &foo;
	x = (*p)(c);
}
