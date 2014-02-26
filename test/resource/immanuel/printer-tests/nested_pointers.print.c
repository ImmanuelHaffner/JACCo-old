int (foo(int (*(*x))));

int (*(*(foo(void))));

struct S
{
	int (*(*x));
	int (*(*(*y)));
};
