






extern void foo (_Decimal32);
_Decimal32 *p;

extern int i;
union U { _Decimal32 a; int b; } u;

void
blatz (void)
{
  _Decimal32 d;
  u.b = i;
  d = u.a;
  foo (d);
}

void
bar (void)
{
  foo (*p);
}
