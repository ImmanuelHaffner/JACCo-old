1

int main()
{
	struct S {
		struct { int a; } x;
	} (*s);
	s->x = 5;
}
