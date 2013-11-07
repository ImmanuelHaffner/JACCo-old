

typedef __builtin_va_list __gnuc_va_list;
typedef __gnuc_va_list va_list;

int a, b;
char c[128];

__attribute__((noinline, noclone)) static void
f1 (const char *fmt, ...)
{
  va_list ap;
  asm volatile ("" : : : "memory");
  if (__builtin_strcmp (fmt, "%s %d %s") != 0)
    __builtin_abort ();
  __builtin_va_start(ap,fmt);
  if (__builtin_strcmp (__builtin_va_arg(ap,const char *), "foo") != 0
      || __builtin_va_arg(ap,int) != 1
      || __builtin_strcmp (__builtin_va_arg(ap,const char *), "bar") != 0)
    __builtin_abort ();
  __builtin_va_end(ap);
}

__attribute__((noinline, noclone)) static void
f2 (const char *fmt, va_list ap)
{
  asm volatile ("" : : : "memory");
  if (__builtin_strcmp (fmt, "baz") != 0
      || __builtin_strcmp (__builtin_va_arg(ap,const char *), "foo") != 0
      || __builtin_va_arg(ap,double) != 12.0
      || __builtin_va_arg(ap,int) != 26)
    __builtin_abort ();
}

static void
f3 (int x, char const *y, va_list z)
{
  f1 ("%s %d %s", x ? "" : "foo", ++a, (y && *y) ? "bar" : "");
  if (y && *y)
    f2 (y, z);
}

__attribute__((noinline, noclone)) void
f4 (int x, char const *y, ...)
{
  va_list z;
  __builtin_va_start(z,y);
  if (!x && *c == '\0')
    ++b;
  f3 (x, y, z);
  __builtin_va_end(z);
}

int
main ()
{
  asm volatile ("" : : : "memory");
  f4 (0, "baz", "foo", 12.0, 26);
  if (a != 1 || b != 1)
    __builtin_abort ();
  return 0;
}
