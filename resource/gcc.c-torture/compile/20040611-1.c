
void foo (char *name)
{
  if (*name)
    name ++;
  while (name[0]);
  asm ("" : "=r" (name));
}
