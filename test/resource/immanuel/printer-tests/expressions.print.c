int (foo())
{
	int x;
	int y;
	int z;
	((y < 3) ? y : z);
	(x = (z, (x + y), (y * x)));
	return z;
}
