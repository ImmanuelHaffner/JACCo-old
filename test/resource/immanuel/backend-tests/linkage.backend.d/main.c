int foo(void);
char * bar();

int main(void)
{
  char *sz;
  sz = bar();
  if ( *sz != 115 /* 's' */ )
    return *sz;
  return foo();
}
