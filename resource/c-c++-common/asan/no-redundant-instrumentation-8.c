



char
foo (int *a, char *b, char *c)
{
  __builtin_memmove (c, b, a[b[0]]);
  return c[0] + b[0];
}
