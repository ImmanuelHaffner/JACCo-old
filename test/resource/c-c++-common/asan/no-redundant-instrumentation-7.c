



char e[200];

struct S
{
  char a[100];
  char b[100];
} s;

int
foo (int *a, char *b, char *c)
{
  int d = __builtin_memcmp (s.a, e, 100);
  d += __builtin_memcmp (s.a, e, 200);
  return d;
}
