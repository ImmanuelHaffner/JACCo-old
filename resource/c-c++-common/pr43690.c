



void
foo (char *x)
{
  asm ("" : : "m" (x++));
  asm ("" : : "m" (++x));
  asm ("" : : "m" (x--));
  asm ("" : : "m" (--x));
  asm ("" : : "m" (x + 1));
}
