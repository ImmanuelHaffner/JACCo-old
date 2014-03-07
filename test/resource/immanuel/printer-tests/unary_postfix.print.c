int (foo())
{
	int x;
	int y;
	int (*(f()));
	int (g());
	int z;
	struct
	{
		struct
		{
			int (*z);
		} y;
	} (*p);
	(++(x--));
	(--(x++));
	(++(x->y));
	(++(f(x, y)));
	((f(x, y))--);
	(*(p->y));
	(*(*((p->y)->z)));
	(*(f()));
}
