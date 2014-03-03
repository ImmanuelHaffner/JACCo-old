int foo()
{
	int x;
	int y;
	int (f());
	int z;
	++x--;
	--x++;
	++x->y;
	++f(x,y);
	f(x, y)--;
	*x->y;
	*(*x->y->z);
	*f();
}
