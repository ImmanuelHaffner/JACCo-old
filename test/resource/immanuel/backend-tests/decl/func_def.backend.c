0


void    f0(void);
char    f1(char, char);
int     f2(int, int);
void  * f3(void);
void  * f4(void *);
char  * f5(void);
int   * f6(void);

int main(int argc, char **argv)
{
  f0();
  f1(0, 0);
  f2(0, 0);
  f3();
  f4(0); // NULL pointer
  f5();
  f6();
  return 0;
}

void    f0(void) { return; }
char    f1(char c0, char c1)    { return 0; }
int     f2(int i0, int i1)      { return 0; }
void  * f3(void)                { return 0; }
void  * f4(void *v)             { return 0; }
char  * f5(void)                { return 0; }
int   * f6(void)                { return 0; }
