int foo(char c)
{
	return 1;
}

int main()
{
	char c;
	char x;
	int (*p)(char);
	p = &foo;
	x = (*p)(c);
}
