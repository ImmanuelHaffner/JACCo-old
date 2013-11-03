
extern void exit (int);
extern void abort (void);
extern void *alloca (long unsigned int);
char *dummy (void);



void *save_ret1[6];
void *test4a (char *);
void *test5a (char *);
void *test6a (char *);

void __attribute__((noinline)) *test1 (void)
{
  void * temp;
  temp = __builtin_return_address (0);
  return temp;
}

void __attribute__((noinline)) *test2 (void)
{
  void * temp;
  dummy ();
  temp = __builtin_return_address (0);
  return temp;
}

void __attribute__((noinline)) *test3 (void)
{
  void * temp;
  temp = __builtin_return_address (0);
  dummy ();
  return temp;
}

void __attribute__((noinline)) *test4 (void)
{
  char * save = (char*) alloca (4);

  return test4a (save);
}

void *__attribute__((noinline)) test4a (char * p)
{
  void * temp;
  temp = __builtin_return_address (1);
  return temp;
}

void __attribute__((noinline)) *test5 (void)
{
  char * save = (char*) alloca (4);

  return test5a (save);
}

void __attribute__((noinline)) *test5a (char * p)
{
  void * temp;
  dummy ();
  temp = __builtin_return_address (1);
  return temp;
}

void __attribute__((noinline)) *test6 (void)
{
  char * save = (char*) alloca (4);

  return test6a (save);
}

void __attribute__((noinline)) *test6a (char * p)
{
  void * temp;
  temp = __builtin_return_address (1);
  dummy ();
  return temp;
}

void *(*func1[6])(void) = { test1, test2, test3, test4, test5, test6 };

char * __attribute__((noinline)) call_func1 (int i)
{
  save_ret1[i] = func1[i] ();
}

static void *ret_addr;
void *save_ret2[6];
void test10a (char *);
void test11a (char *);
void test12a (char *);

void __attribute__((noinline)) test7 (void)
{
  ret_addr = __builtin_return_address (0);
  return;
}

void __attribute__((noinline)) test8 (void)
{
  dummy ();
  ret_addr = __builtin_return_address (0);
  return;
}

void __attribute__((noinline)) test9 (void)
{
  ret_addr = __builtin_return_address (0);
  dummy ();
  return;
}

void __attribute__((noinline)) test10 (void)
{
  char * save = (char*) alloca (4);

  test10a (save);
}

void __attribute__((noinline)) test10a (char * p)
{
  ret_addr = __builtin_return_address (1);
  return;
}

void __attribute__((noinline)) test11 (void)
{
  char * save = (char*) alloca (4);

  test11a (save);
}

void __attribute__((noinline)) test11a (char * p)
{
  dummy ();
  ret_addr = __builtin_return_address (1);
  return;
}

void __attribute__((noinline)) test12 (void)
{
  char * save = (char*) alloca (4);

  test12a (save);
}

void __attribute__((noinline)) test12a (char * p)
{
  ret_addr = __builtin_return_address (1);
  dummy ();
  return;
}

char * dummy (void)
{
  char * save = (char*) alloca (4);

  return save;
}

void (*func2[6])(void) = { test7, test8, test9, test10, test11, test12 };

void __attribute__((noinline)) call_func2 (int i)
{
  func2[i] ();
  save_ret2[i] = ret_addr;
}

int main (void)
{
  int i;

  for (i = 0; i < 6; i++) {
    call_func1(i);
  }

  if (save_ret1[0] != save_ret1[1]
      || save_ret1[1] != save_ret1[2])
    abort ();
  if (save_ret1[3] != save_ret1[4]
      || save_ret1[4] != save_ret1[5])
    abort ();
  if (save_ret1[3] && save_ret1[0] != save_ret1[3])
    abort ();


  for (i = 0; i < 6; i++) {
    call_func2(i);
  }

  if (save_ret2[0] != save_ret2[1]
      || save_ret2[1] != save_ret2[2])
    abort ();
  if (save_ret2[3] != save_ret2[4]
      || save_ret2[4] != save_ret2[5])
    abort ();
  if (save_ret2[3] && save_ret2[0] != save_ret2[3])
    abort ();

  exit (0);
}
