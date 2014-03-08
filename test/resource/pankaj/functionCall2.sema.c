1

int f(void)
{
  return 20;
}
int main()
{
  return (&f + 2)();
}
