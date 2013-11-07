void fib (int *, int);
int fib_serial (int);

int main(void)
{
  int ii = 0, error = 0;
  int fib_result[41], fib_serial_result[41];
  for (ii = 0; ii <= 40; ii++)
    {
      fib (&fib_result[ii], ii);
      fib_serial_result[ii] = fib_serial (ii);
    }

  for (ii = 0; ii <= 40; ii++)
    {
      if (fib_result[ii] != fib_serial_result[ii])
 error = 1;
    }

  return error;
}

int fib_serial (int n)
{
  int x = 0, y = 0;
  if (n < 2)
    return n;
  else
    {
      fib (&x, n-1);
      fib (&y, n-2);
      return (x+y);
    }
}

void fib(int *result, int n)
{
  int x = 0, y = 0;
  if (n < 2)
    x = n;
  else
  {
    _Cilk_spawn fib(&x, n-1);
    fib(&y, n-2);
    _Cilk_sync;
  }
 *result = (x+y);
}
