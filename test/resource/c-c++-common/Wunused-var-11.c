



int i;

void
f1 ()
{
  const int * __attribute__((unused)) a = &i;
  const int *b __attribute__((unused)) = &i;
}
