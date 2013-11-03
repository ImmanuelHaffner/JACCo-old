


int main (void)
{
  int array[10][10], array2[10];
  int x, y;
  x = __sec_reduce_max_ind (array[:][:]);

  y = __sec_reduce_max_ind (array2[:]);

  x = __sec_reduce_min_ind (array[:][:]);

  y = __sec_reduce_min_ind (array2[:]);

  return 0;
}
