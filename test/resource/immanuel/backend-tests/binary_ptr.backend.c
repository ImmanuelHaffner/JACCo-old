0


int main(void)
{
  int  i0;
  int  i1;
  char c0;
  char c1;

  int  *pi0;
  int  *pi1;
  char *pc0;
  char *pc1;

  pi0 = &i0;
  pi1 = &i1;
  pc0 = &c0;
  pc1 = &c1;

  pi0 + 1;
  pc0 + 1;

  4 + pi0;
  4 + pc0;

  pi0 - 2;
  pc0 - 2;


  pi0 - pi1;
  pc0 - pc1;

  return 0;
}
