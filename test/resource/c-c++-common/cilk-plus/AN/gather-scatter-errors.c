

int main (void)
{
  extern int func (int);
  int array[10][10], array2[10];
  int argc = 1;
  array2[array[:][:]] = 5;

  array2[array[:][:]] = 5;
  func (array2[array[:][:]]);
  func (array2[array[argc:func(5)][0:10:2]]);

  array[array2[:]][array2[:]] = 5;
  array[array2[:]][array2[:]] = array2[array[:][:]];
  array[array2[:]][array2[:]] = array2[array[0:10:1][:]];
  array[array2[:]][array2[:]] = array2[array[:][argc:func (argc)]];
  return 0;
}
