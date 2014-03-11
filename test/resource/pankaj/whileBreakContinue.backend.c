2


int main()
{
	int x;
	int y;

  x = 0;
  y = 0;

	while ( x < 5 )
	{
	  if ( x == 3 )
	    break;

	  y = x;
	  x = x + 1;
	}

	return y;
}
