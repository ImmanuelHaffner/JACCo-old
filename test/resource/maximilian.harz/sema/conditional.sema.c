int main()
{
	int i;
	char c;
	void (*v);
	struct S {
		int x;
	} s;
	i = i ? i : i;
	i = c ? i : i;
	c ? *v : *v;
	s = c ? s : s;
}
