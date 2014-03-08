25


struct S { int x; };

void swapArray(struct S * array1, int element1, struct S * array2, int element2)
{
  struct S temp;
  temp = array1[element1];
  array1[element1] = array2[element2];
  array2[element2] = temp;
}

int main()
{
  struct S *array1;
  struct S *array2;

  array1[3].x = 23;
  array2[7].x = 5;
  
  swapArray (array1,3,array2,7);
  return array2[7].x + 2;
}
