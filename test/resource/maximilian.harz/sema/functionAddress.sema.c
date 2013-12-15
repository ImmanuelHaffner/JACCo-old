int foo(char c)
{
	return 1;
}

int main()
{
	int (*p)(char x);
	(p = &foo);
}
