



void
foo (void)
{
  asm goto ("" : : : : lab, lab, lab2, lab);
lab:;
lab2:;
}

void
bar (void)
{
  asm goto ("" : : [lab] "i" (0) : : lab);
lab:;
}

void
baz (void)
{
  int x;
  asm ("" : [lab] "=r" (x) : [lab] "r" (x));
}
