


int main(void)
{
  extern int func(int);
  int array3[:], x, q;
  int array3[1:2:x];
  extern char array3[1:func(x)];
  int *a, ***b;
  extern char *c;
  int array2[10];

  a[:] = 5;
  c[1:2] = 3;
  (array2)[:] = 5;
  b[1:2][1:func(x)][:] = 3;
}
