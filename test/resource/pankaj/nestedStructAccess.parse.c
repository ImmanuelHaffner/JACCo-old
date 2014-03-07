0

int main()
{
	struct
	{
		struct
		{
			struct
			{
				int b;
			} t;
		} s;
	} u;
	u.s.t.b = 2;
	return 0;
}
