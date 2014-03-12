5


void* malloc(int);

int main()
{
  int *a;
  a = malloc(sizeof(int) * 10);
  return &a[5] - &a[0];
}
