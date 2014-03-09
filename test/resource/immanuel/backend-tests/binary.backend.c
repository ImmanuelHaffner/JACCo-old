0


int main(void)
{
  int a;
  char b;

  a = 42;
  b = 13;

  if ( a + b != 55 )      return   1;
  if ( a - b != 29 )      return   2;
  if ( b - a != -29 )     return   3;
  if ( a * b != 546 )     return   4;
  if ( a / b != 3 )       return   5;
  if ( b / a != 0 )       return   6;
  if ( a % b != 3 )       return   7;
  if ( b % a != 13 )      return   8;
  if ( a << 1 != 84 )     return   9;
  if ( a >> 1 != 21 )     return  10;
  if ( b << 1 != 26 )     return  11;
  if ( b >> 1 != 6 )      return  12;
  if ( ( a < b ) == 1 )   return  13;
  if ( ( a > b ) == 0 )   return  14;
  if ( ( a <= b ) == 1 )  return  13;
  if ( ( a >= b ) == 0 )  return  14;

  return 0;
}
