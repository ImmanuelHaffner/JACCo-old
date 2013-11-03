static char tab[4] = {0};

static int
test0 ()
{


  tab[0] = 1;
  tab[1] = 2;



  char t0 = tab[1];



  char t1 = tab[1];

  return t0 + t1;
}

static int
test1 ()
{


  char foo[4] = {1};



  __builtin_memset (tab, 3, sizeof (tab));


  __builtin_memset (tab, 4, sizeof (tab));
  __builtin_memset (tab, 5, sizeof (tab));




  __builtin_memcpy (&tab[1], foo, 3);



  return tab[1];



}

int
main ()
{
  return test0 () && test1 ();
}
