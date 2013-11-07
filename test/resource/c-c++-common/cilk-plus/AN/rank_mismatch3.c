

int funct (int x, int y);
void funct_void (int x, int y, int z);
int main(void)
{
  int y, array[100], array2[100], array3[100][100], array4[100];

  array[:] = ((array2[:] + array[:]) * array4[:]) + array3[:][:];
  array[:] = funct (array2[:], array3[:][:]);
  array[:] = array3[:][:];
  array3[:][:] = array[:];
  array3[:][:] = array[5];
  funct_void (array2[:], array3[:][:], array[:]);
  funct_void (array2[:], array3[:][:], array[:]);
  funct_void (array3[:][:], array2[:], array[:]);
  funct_void (array2[:], array[:], array3[:][0:10:1]);
  return 0;
}
