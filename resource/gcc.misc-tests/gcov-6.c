extern void exit (int);

int val;

void
foo (int i)
{

  if (i < 0)


    exit (0);

  val += i;
}

int
main()
{
  int i;


  foo (100);

  for (i = 2; i > -10; i--)

    foo (i);

}
