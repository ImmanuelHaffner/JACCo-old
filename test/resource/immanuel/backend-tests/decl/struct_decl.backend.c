0


struct S
{
  char c;
  int n;

  void *pv;
  char *pc;
  int *pn;

  void **ppv;
  char **ppc;
  int **ppn;

  struct S *ps;
  struct S **pps;
};

struct Q
{
  struct S s;
  struct S *ps;
  struct Q *pq;
};

int main(void)
{
  struct S s;
  struct Q q;
  return 0;
}
