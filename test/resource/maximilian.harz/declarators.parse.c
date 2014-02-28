0

int main()
{
  sizeof(int ((*)(int(void))));
  return 1;
}

int fun(int (f)(int, int *(void (x)()))) {
  return 1;
}
int fun2(int f(int (((y))), int *(void (x)())));

int fun3(int (f(int)));
int fun7(int ((int)));

int fun4(int ((*f)(int)), void * p, int (*i));

int g(struct {int (x);int y;} s, int(void (h(int))));
int h(struct s, int(void (h(int))));
int ig(struct s, int(void (h(int))));

int (*r(void *(void (*blubb)(int))(int))(int));


char *(*p()(int));
int foo(char *(*()(int)));
