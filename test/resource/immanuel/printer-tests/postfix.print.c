int (foo())
{
	struct S
	{
		int a;
	} x;
	char (*a);
	struct S (*p);
	int y;
	void (f());
	(x.a);
	(p->a);
	(y++);
	(y--);
	(a[y]);
	(f(x, y));
}
