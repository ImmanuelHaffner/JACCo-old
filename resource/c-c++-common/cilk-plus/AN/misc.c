


int main (void)
{
  int array[10], array2[10][10];
  int x, ii, jj ;

  switch (array[:]) {
  case 1:
    x = 5;
    break;
  case 2:
    x = 2;
    break;
  default:
    x = 9;
  }

  switch (array2[:][:]) {
  case 1:
    x = 5;
    break;
  case 2:
    x = 2;
    break;
  default:
    x = 9;
  }

  switch (array[:] + x) {
  case 1:
    x = 5;
    break;
  case 2:
    x = 2;
    break;
  default:
    x = 9;
  }

  switch (array2[:][1:x:4] + x) {
  case 1:
    x = 5;
    break;
  case 2:
    x = 2;
    break;
  default:
    x = 9;
  }

  for (ii = 0; ii < array[:]; ii++)
    {
      x = 2;
    }

  for (ii = 0; ii < array2[:][:]; ii++)
    {
      x = 3;
    }

  for (; array2[:][:] < 2;)
    x = 4;


  while (array2[:][:])
    x = 3;

  while (array[1:1:1])
    x = 1;

  while (ii != array2[1:x:3][1:2:1])
    x = 2;

  do {
    x = 3;
  } while (ii != array2[:][:]);

  do {
    x = 2;
  } while (ii != (x + array2[:][1:x:2]) + 2);

  do {
    x += 3;
    if (x == 5)
      return array2[:][:];
  } while (ii != 0);

  for (ii = 0; ii < 10; ii++)
    if (ii % 2)
      return array[1:x:ii];

  for (ii = 0; ii < x; ii++)
    if (ii)
      return array2[:][:];

  for (array[:] = 0; ii < x; ii++)
    x= 2;

  for (ii = 0; ii < 10; array[:]++)
    x = 5;

  for (jj = 0; jj < 10; array2[:][:]++)
    x = 3;

  for (jj = 0; jj < 10; array2[:][1:x:4]++, jj++)
    x = 3;

  return x;
}
