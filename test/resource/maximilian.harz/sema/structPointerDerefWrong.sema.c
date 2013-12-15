int main()
{
	struct S {
		char (*x);
	} (*s);
	(*s).x = 5;
}
