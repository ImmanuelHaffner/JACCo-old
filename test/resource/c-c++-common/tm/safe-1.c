


void ts(void) __attribute__((transaction_safe));
void tp(void) __attribute__((transaction_pure));
void tc(void) __attribute__((transaction_callable));
void ti(void) __attribute__((transaction_unsafe));
void tm(void) __attribute__((transaction_may_cancel_outer));
void tu(void);
int fc(int) __attribute__((const));

typedef void (*Fs) (void) __attribute__((transaction_safe));
typedef void (*Fc) (void) __attribute__((transaction_callable));
typedef void (*Fi) (void) __attribute__((transaction_unsafe));
typedef void (*Fm) (void) __attribute__((transaction_may_cancel_outer));
extern Fs ps;
extern Fc pc;
extern Fi pi;
extern Fm pm;
extern void (*pu)(void);

int __attribute__((transaction_safe))
foo(void)
{
  int i;

  ts();
  tp();
  tc();
  ti();






  (*ps)();
  (*pc)();
  (*pi)();
  (*pu)();

  asm("");
  asm("" : "=g"(i));

  return fc(i);
}

int __attribute__((transaction_may_cancel_outer))
bar(void)
{
  int i;

  ts();
  tp();
  tc();
  ti();
  tm();

  (*ps)();
  (*pc)();
  (*pi)();
  (*pm)();
  (*pu)();

  asm("");
  asm("" : "=g"(i));

  return fc(i);
}
