struct A { int i; };
struct B { struct A a; };

void f(struct A*, struct A*);


void bar(_Bool b)
{
  struct B * D1601;
  struct A D1576;
  struct A * D1593;
  struct B * D1592;
  struct B D1575;

  D1575 = (struct B){};

  if (b) D1592 = &D1575; else D1592 = &D1575;

  D1593 = &D1592->a;
  D1576 = (struct A){};
  f (D1593, &D1576);
}
