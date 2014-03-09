1


void swapArray(char *array1, int element1, char *array2, int element2)
{
  char temp;
  temp = array1[element1];
  array1[element1] = array2[element2];
  array2[element2] = temp;
}

int main()
{
  char *string1;
  char *string2;

  string1 = "doof";
  string2 = "dumm";

  swapArray (string1,3,string2,3);
  return string1[1] == string2[0];
}
