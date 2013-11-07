int func (int *x)
{
  int q = *x;
   q++;
   *x = q;



   return *x;
}
int main (void)
{
  char array[1000], array2[1000];
  int ii, d = 2;

  for (ii = 0; ii < 1000; ii++) {
   array[ii] = 5;
   array2[ii]= 2;
  }

  d = func (&d);
  array2[:] = d * array[:] + (char) func (&d);




  for (ii = 0; ii < 1000; ii++)
    if (array2[ii] != (3 * 5 + 4))
      return 1;

  return 0;
}
