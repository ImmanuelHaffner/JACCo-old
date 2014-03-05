int (foo())
{
t1:
	goto t0;
t2:
	goto t1;
	{
t0:
		goto t2;
	}
}
