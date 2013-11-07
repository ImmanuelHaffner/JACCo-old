




struct A
{
  const char *p;
};

struct B
{
    char p[10];
    struct A a;
};

void
f0 ()
{
  __builtin_offsetof(struct A, p);
  __builtin_offsetof(struct A, p[0]);
  __builtin_offsetof(struct B, p[0]);
  __builtin_offsetof(struct B, p[9]);
  __builtin_offsetof(struct B, p[10]);
  __builtin_offsetof(struct B, p[11]);
  __builtin_offsetof(struct B, a.p);
  __builtin_offsetof(struct B, p[0]);
  __builtin_offsetof(struct B, a.p[0]);
}
