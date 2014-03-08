2


int main()
{

	int x;
	int y;
	while(x < 5)
	{
	  if(x == 3)
	  {
	    break;
	  }
	  y = x;
	  x = x + 1;
	}
	return y;
}
