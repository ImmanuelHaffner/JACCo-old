char b;

int c;

void (*e);

char (*f);

int (*g);

struct S (*h);

struct S
{
	int x;
	char (*y), z;
	struct S (*t);
} (*x);

struct S2
{
	int x;
};

struct S3
{
	struct Q (*q);
	struct Q
	{
		int x;
		char y, z;
		struct S (*s);
	};
	struct Q p;
};

struct S4 (*((*f2)()));

struct S5
{
	int x;
} (*((*f3)()));

void (*((*f4)(struct S (*s))));
