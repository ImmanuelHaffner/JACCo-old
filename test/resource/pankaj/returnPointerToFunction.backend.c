100


int f(int x)
{
  return x;
}

int (*g(void))(int)
{
  return f;
}

int main()
{
  return (g())(100);
}
