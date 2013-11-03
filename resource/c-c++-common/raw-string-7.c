






const char *s0 = R"()";




const char *s1 = R"()";



int
main (void)
{
  if (__builtin_strcmp (s0, "\\ \n") != 0
      || __builtin_strcmp (s1, "\\\t\n") != 0)
    __builtin_abort ();
  return 0;
}
