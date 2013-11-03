

extern void abort(void);

static void foo(int arg)
{
  if (arg != 5)
    abort();
}

static void bar(int arg)
{
  foo(arg);
  __builtin_apply(foo, __builtin_apply_args(), 16);
}

int main(void)
{
  bar(5);

  return 0;
}
