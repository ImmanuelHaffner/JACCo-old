9


void* malloc(int);

int main()
{
  char *p;
  p = malloc(sizeof(char) * 10);
  return &p[9] - &p[0];
}
