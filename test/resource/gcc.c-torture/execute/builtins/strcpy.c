





extern void abort (void);
extern char *strcpy (char *, const char *);
typedef long unsigned int size_t;
extern void *memcpy (void *, const void *, size_t);
extern int memcmp (const void *, const void *, size_t);

char p[32] = "";

void
main_test (void)
{
  if (strcpy (p, "abcde") != p || memcmp (p, "abcde", 6))
    abort ();
  if (strcpy (p + 16, "vwxyz" + 1) != p + 16 || memcmp (p + 16, "wxyz", 5))
    abort ();
  if (strcpy (p + 1, "") != p + 1 || memcmp (p, "a\0cde", 6))
    abort ();
  if (strcpy (p + 3, "fghij") != p + 3 || memcmp (p, "a\0cfghij", 9))
    abort ();
  if (memcpy (p, "ABCDE", 6) != p || memcmp (p, "ABCDE", 6))
    abort ();
  if (memcpy (p + 16, "VWX" + 1, 2) != p + 16 || memcmp (p + 16, "WXyz", 5))
    abort ();
  if (memcpy (p + 1, "", 1) != p + 1 || memcmp (p, "A\0CDE", 6))
    abort ();
  if (memcpy (p + 3, "FGHI", 4) != p + 3 || memcmp (p, "A\0CFGHIj", 9))
    abort ();



  if (__builtin_strcpy (p, "abcde") != p || memcmp (p, "abcde", 6))
    abort ();
  if (__builtin_memcpy (p, "ABCDE", 6) != p || memcmp (p, "ABCDE", 6))
    abort ();
}
