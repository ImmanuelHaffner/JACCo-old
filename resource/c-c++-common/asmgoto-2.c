


void
foo (void)
{
  __label__ lab;
  int i = 0;
  asm goto ("" : : : : lab);
  asm goto ("" : "=r" (i) : : : lab);
  asm goto ("" : : : : );
  asm goto ("" : : : "memory");
  asm goto ("" : : : );
  asm goto ("" : : "r" (i));
  asm goto ("" : : );
  asm goto ("" : "=r" (i));
  asm goto ("" : );
  asm goto ("");
  lab:;
}
