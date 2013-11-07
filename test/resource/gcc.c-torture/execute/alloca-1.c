



typedef long unsigned int size_t;

struct dummy { int x __attribute__((aligned)); };


_Bool foo(void)
{
  char *p = __builtin_alloca(32);
  return ((size_t)p & (__alignof__(struct dummy) - 1)) == 0;
}

int main()
{
  if (!foo())
    abort ();
  return 0;
}
