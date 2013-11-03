


void foo (float * __restrict__ a, float * __restrict__ b, int n, int j)
{
  int i;
  for(i = 0; i < n; ++i)
    a[i] = (b[j+50] + b[j-50]) * 0.5f;
}
