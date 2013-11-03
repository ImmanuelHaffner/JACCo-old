float array4[20][20][20][20];
int main(void)
{
  int array[20][20], array2[20], array3[20], x = 0, y;
  int x_correct, y_correct, ii, jj = 0, kk = 0, ll = 0;
  for (ii = 0; ii < 20; ii++)
    {
      for (jj = 0; jj < 20; jj++)
 {
   array[ii][jj] = 1+ii;
   array2[ii]= 2;
   array3[ii]= 3;
 }
    }

  array[array2[:]][array3[:]] = 1000;

  for (ii = 0; ii < 20; ii++)
    if (array[array2[ii]][array3[ii]] != 1000)
      return 1;
  array4[array2[:]][array3[0:20:1]][array2[0:20:1]][array3[0:20:1]] =
    (float)array[array2[:]][array3[:]];

  for (ii = 0; ii < 20; ii++)
    if (array4[array2[ii]][array3[ii]][array2[ii]][array3[ii]] !=
 (float)array[array2[ii]][array3[ii]])
      return 2;
  return 0;
}
