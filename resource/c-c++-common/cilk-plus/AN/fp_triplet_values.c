


float q;

void func (int *x)
{
  *x = 5;
}

int main (void)
{
  int array[10], array2[10];
  array2[:] = array[1.5:2];
  array2[:] = array[1:2.32333333333];
  array2[1:2:1.5] = array[:];
  func (&array2[1:2.34:3]);
  array2[1.43:9]++;
  array2[1:9.3]++;
  array2[1:9:0.3]++;

  ++array2[1:q:3];
  array2[:] = array[q:1:3];
  array2[:] = array[1:q:3];
  array2[:] = array[1:3:q];
  func (&array2[1:q:3]);
  return 0;
}
