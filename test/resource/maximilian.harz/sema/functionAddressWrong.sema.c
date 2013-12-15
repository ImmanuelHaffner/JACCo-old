int foo(char c)
{
	return 1;
}

int main()
{
	char (*p)(char x);
	(p = &foo);
}
