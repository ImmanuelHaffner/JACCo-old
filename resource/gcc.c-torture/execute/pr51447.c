

extern void abort (void);


register void *ptr asm ("rbx");




int
main (void)
{
  __label__ nonlocal_lab;
  __attribute__((noinline, noclone)) void
    bar (void *func)
      {
 ptr = func;
 goto nonlocal_lab;
      }
  bar (&&nonlocal_lab);
  return 1;
nonlocal_lab:
  if (ptr != &&nonlocal_lab)
    abort ();
  return 0;
}
