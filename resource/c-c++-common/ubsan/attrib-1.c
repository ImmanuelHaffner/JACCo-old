



__attribute__((no_sanitize_undefined)) int
f1 (int i)
{
  return 16 << i;
}

int f2 (int i);
int f2 (int i) __attribute__((no_sanitize_undefined));
int f2 (int i) __attribute__((no_sanitize_undefined));
int f2 (int i);

int
f2 (int i)
{
  return 1 / i;
}

void f3 (void);
__typeof (f3) f3 __attribute__((__no_sanitize_undefined__));

void
f3 (void)
{
  __builtin_unreachable ();
}
