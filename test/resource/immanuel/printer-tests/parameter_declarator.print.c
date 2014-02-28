int (f0(int (*a), int (*(*b)), struct S (*(*s))));

int (fx(int (*a), int (*(*b)), struct S (*(*s))))
{
	return 0;
}

struct S
{
	int (*(*x));
	struct S (*next);
} s;

int (f1(struct S (*(*s0)), struct S (*(*s1))));

char (*(*(f2(int (*(*x))))));

char (*(*(*((*(*g0))(struct S (*(*s)))))));

char (*(*(*((*(*g1))(struct T
{
	int x;
	char y;
} (*(*s)))))));

char (*((*g2)(int ((*p)(void)))));

int (*(f3(void ((*p)(int)), int x)));
