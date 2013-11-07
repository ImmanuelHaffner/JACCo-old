

void
foo (void)
{
  asm volatile ("" : "+m" (*(volatile unsigned short *) 0x1001UL));
}
