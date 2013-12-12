void foo()
{
	int x;
	int y;
	int z;
	(x = ((y > 3) ? y : z));
	(z *= (((x * y) ^ y) << x));
	(x = (z, (x + y), (y / x)));
	return z;
}
