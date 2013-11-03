


int function_call (int x);
int function_call (int x)
{
  return x;
}

int main (void)
{
  int array[100], array2[100][100];
  int argc = 4;
  array[:] = array[:] + array2[:][:];

  if (array[:] + array2[:][:])
    return argc == 5;

  argc += function_call (array[:] + array2[5:10:2][:]);

  argc += function_call (function_call (array[:] + array2[5:10:2][:]));

   argc += __sec_reduce_add (array[:], array2[:][:]);

   argc += __sec_reduce_add (array2[:][:]) + argc;
  return argc;
}
