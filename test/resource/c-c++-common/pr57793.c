

struct A { unsigned a : 1; unsigned b : 1; };
struct B
{
  unsigned char c[0x40000000];
  unsigned char d[0x40000ff0];
  struct A e;
};

void *foo (struct B *p)
{
  if (p->e.a)
    return (void *) 0;
  p->e.b = 1;
  return p->c;
}

void
bar (struct B *p)
{
  foo (p);
}
