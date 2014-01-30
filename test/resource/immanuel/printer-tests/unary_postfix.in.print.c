int foo()
{
	++x--;
	--x++;
	++x->y;
	++f(x,y);
	f(x, y)--;
	*x->y;
	*(*x->y->z);
	*f();
}
