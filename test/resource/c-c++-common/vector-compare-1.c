void
foo (__attribute__((vector_size((4)*sizeof(int)))) int x, __attribute__((vector_size((4)*sizeof(float)))) float y)
{
  __attribute__((vector_size((4)*sizeof(int)))) int p4;
  __attribute__((vector_size((4)*sizeof(int)))) int r4;
  __attribute__((vector_size((4)*sizeof(unsigned int)))) unsigned int q4;
  __attribute__((vector_size((8)*sizeof(int)))) int r8;
  __attribute__((vector_size((4)*sizeof(float)))) float f4;

  r4 = x > y;
  r8 = (x != p4);
  r8 == r4;
}
