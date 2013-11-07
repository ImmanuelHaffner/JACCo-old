






extern int printf (const char *, ...);
extern int printf_unlocked (const char *, ...);
extern void abort(void);

void
main_test (void)
{
  const char *const s1 = "hello world";
  const char *const s2[] = { s1, 0 }, *const*s3;

  printf ("%s\n", "hello");
  printf ("%s\n", *s2);
  s3 = s2;
  printf ("%s\n", *s3++);
  if (s3 != s2+1 || *s3 != 0)
    abort();

  printf ("%c", '\n');
  printf ("%c", **s2);
  s3 = s2;
  printf ("%c", **s3++);
  if (s3 != s2+1 || *s3 != 0)
    abort();

  printf ("");
  printf ("%s", "");
  printf ("\n");
  printf ("%s", "\n");
  printf ("hello world\n");
  printf ("%s", "hello world\n");



  __builtin_printf ("%s\n", "hello");


  __builtin_putchar ('\n');
  __builtin_puts ("hello");


  printf_unlocked ("");
  __builtin_printf_unlocked ("");
  printf_unlocked ("%s", "");
  __builtin_printf_unlocked ("%s", "");
}
