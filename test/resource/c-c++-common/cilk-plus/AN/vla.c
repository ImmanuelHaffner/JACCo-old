


int func (int x)
{
  return x++;
}
int main(void)
{
  int argc = 1;
  __asm volatile ("" : "+r" (argc));
  int array[argc];

  array[:] = 5;
  array[0:argc] = 5;
  array[0:5:2] = 5;
  array[0:argc:2] = 5;
  array[0:argc:func (argc-2)] = 5;
  return 0;
}
