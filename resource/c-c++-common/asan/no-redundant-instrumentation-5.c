



void
foo (int *a, char *b, char *c)
{
  __builtin_memmove (c, b, a[b[0]]);
}
