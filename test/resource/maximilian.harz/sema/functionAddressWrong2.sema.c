int foo(char c)
{
	return 1;
}

int main()
{
	int (*p)(int x);
	(p = &foo);
}
