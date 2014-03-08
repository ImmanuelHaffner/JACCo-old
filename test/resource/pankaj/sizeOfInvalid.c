1

int f(void)
{
	int x;
	return x = 2;
}
int main()
{
	int x;
	return x = sizeof(f);
}
