


extern void link_error (void);

void bar0 (int * __restrict__ arr1, int * __restrict__ arr2)
{
  arr1[0] = 1;
  arr2[0] = 1;
  if (arr1[0] != 1)
    link_error ();
}

int main()
{
  return 0;
}
