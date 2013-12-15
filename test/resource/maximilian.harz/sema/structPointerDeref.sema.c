int main()
{
	struct S {
		int x;
	} (*s);
	(*s).x = 5;
}
