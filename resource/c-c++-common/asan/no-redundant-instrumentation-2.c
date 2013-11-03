int
main ()
{
  char tab[5];



  __builtin_memset (tab, 1, sizeof (tab));


  __builtin_memset (tab, 1, 3);
}
