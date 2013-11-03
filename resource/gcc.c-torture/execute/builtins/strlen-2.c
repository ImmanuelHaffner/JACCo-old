





typedef long unsigned int size_t;
extern size_t strlen (const char *);
extern char *strcpy (char *, const char *);
extern int memcmp (const void *, const void *, size_t);
extern void abort (void);
extern int inside_main;

size_t g, h, i, j, k, l;

size_t
foo (void)
{
  if (l)
    abort ();
  return ++l;
}

void
main_test (void)
{
  if (strlen (i ? "foo" + 1 : j ? "bar" + 1 : "baz" + 1) != 2)
    abort ();
  if (strlen (g++ ? "foo" : "bar") != 3 || g != 1)
    abort ();
  if (strlen (h++ ? "xfoo" + 1 : "bar") != 3 || h != 1)
    abort ();
  if (strlen ((i++, "baz")) != 3 || i != 1)
    abort ();

  inside_main = 0;
  if (strlen (j ? "foo" + k++ : "bar" + k++) != 3 || k != 1)
    abort ();
  if (strlen (foo () ? "foo" : "bar") != 3 || l != 1)
    abort ();
}
