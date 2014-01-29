struct S;

struct S (*(foo()));

struct P
{
	int x, y;
	char z;
} (bar());

struct Q
{
	int x;
	char y;
	int z;
} (*(foobar()));

struct R
{
	int x;
	char y;
	int z;
} (*(f()))
{
	struct R r;
	return (&r);
}
