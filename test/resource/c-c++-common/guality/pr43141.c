


int i;
static int f(int) __attribute ((noinline));
static int f(int x)
{
  return i;
}

int main()
{
  return f(42);
}
