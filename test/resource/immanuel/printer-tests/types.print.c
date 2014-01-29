void a;

char b;

int c;

struct S d;

void (*e);

char (*f);

int (*g);

struct S (*h);

struct S
{
	int x;
	char (*y), z;
	struct S s;
	struct S (*t);
} (*x);

struct S
{
	int x;
};

struct S
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

struct S (*((*f)()));

struct S
{
	int x;
} (*((*f)()));

void (*((*f)(struct S (*s))));
