void my_func (double *x, double y)
{
  if (*x < y)
    *x = y;
}


int main(void)
{
  int ii,array[100], y = 0, y_int = 0, array2[100];
  double x = 0.000, yy, array3[100], array4[100];
  double max_value = 0.000, min_value = 0.000, add_value, mul_value = 1.00;
  int max_index = 0, min_index = 0;

  for (ii = 0; ii < 100; ii++)
    {
      array[ii] = 1+ii;
      array2[ii]= 2;
    }

  for (ii = 0; ii < 100; ii++)
    {
      if (ii%2 && ii)
 array3[ii] = (double)(1.0000/(double)ii);
      else
 array3[ii] = (double) ii + 0.10;
      array4[ii] = (double) (1.00000/ (double)(ii+1));
    }


  __sec_reduce_mutating (&x, array3[:] * array4[:], my_func);

  y = __sec_reduce_max_ind ( array3[:] * array4[:]);


  max_value = array3[0] * array4[0];
  for (ii = 0; ii < 100; ii++)
    if (array3[ii] * array4[ii] > max_value) {
      max_index = ii;
    }

  for (ii = 0; ii < 100; ii++)
    my_func (&max_value, array3[ii] * array4[ii]);
  if (x != max_value)
    return 1;

  if (y != max_index)
    return 2;

  return 0;
}
