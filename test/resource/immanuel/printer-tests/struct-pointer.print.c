int (foo(struct S (*s)))
{
	struct
	{
		int x, y;
	} (*s);
	return 9;
}
