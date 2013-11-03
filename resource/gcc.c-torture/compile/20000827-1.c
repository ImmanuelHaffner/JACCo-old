


int
foo ()
{
  while (1)
    {
      int a;
      char b;


      __asm__("":"=r" (a)); __asm__("":"=r" (b));
      if (b)
 return a;
    }
}
