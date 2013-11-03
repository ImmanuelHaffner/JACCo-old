int func1(int x)
{

  return (x - 2);
}

int func2(int x)
{

  return (x * 500);
}

int func3 (int x)
{


  return (x-1);
}

int func4(int x)
{
  if (x > 0)
    return x;
  else
    return x--;
}



int main (void)
{
  int argc = 1;
  int array[2500];


  __asm volatile ("" : "+r" (argc));

  array[argc-1:func2(++argc):1] = 5;
  array[1000:500:1] = 10;
  array[1500:500:1] = 15;
  array[2000:500:1] = 20;
  array[2000:500:1] = 25;
  array[2000:500:1] = 30;

  argc = func3 (argc);
  if (array[func3(argc):func2(++argc)] != 5) {



    return 1;
  }


  if (func4(array[func2(argc)-1:func2(argc--):func1(argc)]) != 5) {



    return 2;
  }


  if (func4 (func4(array[func2(argc++):500: func1(argc--)])) != 5) {



    return 3;
  }

  return 0;
}
