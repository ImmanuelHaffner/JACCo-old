






static void __attribute__ ((noinline)) Recursive (void);



static void __attribute__ ((noinline))
Recursive ()
{
  return;
}



static void __attribute__ ((noinline)) Recursive (void);
int main ()
{
  Recursive ();
  return 0;
}
