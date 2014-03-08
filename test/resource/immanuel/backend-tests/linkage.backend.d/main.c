int foo(void);
char * bar();

int main(void)
{
  char *sz;
  sz = bar();
  return foo();
}
