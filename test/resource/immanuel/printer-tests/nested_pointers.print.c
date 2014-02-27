int (foo(int (*(*x))));

int (*(*(foo2(void))));

struct S
{
	int (*(*x));
	int (*(*(*y)));
};
