extern void abort (void);
extern char *strcpy (char *, const char *);
typedef long unsigned int size_t;
extern void *memcpy (void *, const void *, size_t);
extern int memcmp (const void *, const void *, size_t);

char buf[32], *p;
int i;

char *
__attribute__((noinline))
test (void)
{
  int j;
  const char *q = "abcdefg";
  for (j = 0; j < 3; ++j)
    {
      if (j == i)
        q = "bcdefgh";
      else if (j == i + 1)
        q = "cdefghi";
      else if (j == i + 2)
        q = "defghij";
    }
  p = strcpy (buf, q);
  return strcpy (buf + 16, q);
}

void
main_test (void)
{



  if (test () != buf + 16 || p != buf)
    abort ();

}
