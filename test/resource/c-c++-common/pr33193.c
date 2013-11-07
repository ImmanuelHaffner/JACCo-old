


struct a {float x, y; };

float f(struct a b)
{


  float x = __real b;
  float y = __imag b;
  return x / y;
}
int f1(int *b)
{
  float x = __imag b;
  float y = __real b;
  return x - y;
}
