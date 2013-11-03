




int main(void)
{
  int jj, kk, array_3C[20][20][20];
  int ii,array[20], y = 0, y_int = 0, array2[20],
      array_3[20][20][20];
  double x, yy, array3[20], array4[20];

  array[:] = __sec_implicit_index (0);
  array_3[:][:][:] = __sec_implicit_index (1) + __sec_implicit_index(0) +
    __sec_implicit_index (2);

  for (ii = 0; ii < 20; ii++)
    for (jj = 0; jj < 20; jj++)
      for (kk = 0; kk < 20; kk++)
 array_3C[ii][jj][kk] = ii+jj+kk;

  for (ii = 0; ii < 20; ii++)
    for (jj = 0; jj < 20; jj++)
      for (kk = 0; kk < 20; kk++)
 if (array_3[ii][jj][kk] != array_3C[ii][jj][kk])
   return 1;

  return 0;
}
