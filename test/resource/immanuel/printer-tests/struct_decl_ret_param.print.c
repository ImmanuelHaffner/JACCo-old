struct S
{
	int x;
	char y;
} (*(foo()))
{
	struct S x;
	return (&x);
}
